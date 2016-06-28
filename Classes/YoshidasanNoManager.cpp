#include "YoshidasanNoManager.h"


//YoshidasanNoManager *YoshidasanNoManager::create()
//{
//
//	YoshidasanNoManager *pRet = new YoshidasanNoManager();
//	if (pRet && pRet->init(nullptr))
//	{
//		pRet->autorelease();
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = NULL;
//		return NULL;
//	}
//}


bool YoshidasanNoManager::init(StageCreater *stageCrater, Kusahayasu *kusahayasu)
{
	if (!Node::init())return false;

	//stage作るクラス
	_stageCrater = stageCrater;

	//Kusahayasuくらす
	_kusahayasu = kusahayasu;

	//吉田さんの数
	int yoshidaSuu = 30;

	_goolRect = _stageCrater->getGoolRect();

	//吉田さんの生成
	for (int i = 0; i < yoshidaSuu; i++)
	{
		const char * yoshidaPas;
		//吉田のステ
		bool yankiCheck = false;
		float gravity = -0.8f;
		int maxSpeed = 6;
		int myNo = rand() % 4;

		switch (myNo)
		{
		case 0://いつもの
			yoshidaPas = "pix/actor/yoshidasan.png";
			gravity *= 1.0f;
			maxSpeed *= 1.0f;
			break;
		case 1://女
			yoshidaPas = "pix/actor/yoshidagirl.png";
			gravity *= 0.8f;
			maxSpeed *= 1.1f;
			break;
		case 2://でぶ
			yoshidaPas = "pix/actor/yoshidadebu.png";
			gravity *= 1.1f;
			maxSpeed *= 0.8f;
			break;
		case 3://ヤンキー
			yoshidaPas = "pix/actor/yoshidasanyanki.png";
			gravity *= 1.0f;
			maxSpeed *= 0.9f;
			yankiCheck = true;
			break;
		default://保険
			yoshidaPas = "pix/actor/yoshidasan.png";
			gravity *= 1.0f;
			maxSpeed *= 1.0f;
			break;
		}

		Yoshidasan *yoshida = new Yoshidasan();
		yoshida->init(yoshidaPas, maxSpeed, gravity, yankiCheck, myNo);
		yoshida->autorelease();
		_yoshida.pushBack(yoshida);
		addChild(_yoshida.at(i));
		_yoshida.at(i)->setPosition(100, designResolutionSize.height * 0.9f);
		_yoshida.at(i)->startGo(Vec2(rand() % (int)designResolutionSize.width*0.2, -rand() % (int)designResolutionSize.height * 0.1f), 1);
	}

	_syougaibutu = _stageCrater->getSyougaibutu();

	_touchStartPos = Vec2(0, 0);
	_yoshidaCenterPos = Vec2(0, 0);
	_kumomoAngle = 0.0f;
	_haniAngle = 0;

	_windRange = 0.0f;
	_windCallCnt = 0.0f;

	//updateを毎フレーム実行するように登録する
	this->scheduleUpdate();

	return true;
}

void YoshidasanNoManager::update(float dt)
{
	_frmCount += dt;
	if ((int)_frmCount % 5 == 0)
	{
		yoshidaCenterCall();
		_frmCount = 0;
	}
	if (_windCallCnt > 0)
	{
		_windCallCnt -= dt;
		kazeKeisan();
	}

	yoshidaNoAtarihantei();
	yoshidaWatashi();

}

void YoshidasanNoManager::touchEndCall(int haniAngle, float windRange, float angle, Vec2 touchStartPos, Vec2 windEndPos, float windTime)
{
	_touchStartPos = touchStartPos;
	_windRange = windRange;
	_haniAngle = haniAngle;
	_kumomoAngle = angle;
	_kumomoAngle += _kumomoAngle > 0 ? 0 : 360;
	_touchStartPos = touchStartPos;
	_windCallCnt = windTime;

	angle = angle * 180 / M_PI;
	_effectManager->kazeNagareru(_touchStartPos, windEndPos, angle, _windCallCnt);

	for (auto yoshida : _yoshida)
	{
		yoshida->_isWind = false;
	}
}

void YoshidasanNoManager::yosidaLiveingCheck()
{
	if (_yoshida.size() == 0)
	{
		_kusahayasu->reStart();
	}
}

void YoshidasanNoManager::yoshidaNoAtarihantei()
{
	vector<Sprite*> shinikusa = _kusahayasu->getShinikusa();

	for (int target = 0; target < _yoshida.size(); target++)
	{
		if (!_yoshida.at(target)->_isGool)
		{
			bool isHit = false;
			Rect targetRect = _yoshida.at(target)->getBoundingBox();
			float yoshidaSize = targetRect.size.width;
			//_effectManager->creatKirakira(_yoshida.at(target)->getPosition());
			targetRect = Rect{
				targetRect.getMinX() + yoshidaSize*0.45f,
				targetRect.getMinY() + yoshidaSize*0.25f,
				yoshidaSize*0.40f,
				yoshidaSize*0.40f };

			//ごーると当たっているか
			if (targetRect.intersectsRect(_goolRect))
			{
				float dilayTime = 1.0f;

				int targetNo = _yoshida.at(target)->_myNo;
				_yoshida.at(target)->actionGoolMove(Vec2(_goolRect.getMidX(), _goolRect.getMidY()), dilayTime);
				_yoshida.erase(_yoshida.begin() + target);
				_kusahayasu->scorePlus(targetNo);
				auto dilay = DelayTime::create(dilayTime + 0.2f);
				auto func = CallFunc::create([=]()
				{
					_kusahayasu->kusahayasu(
						Vec2(_goolRect.getMinX() + 20 + rand() % (int)((_goolRect.getMaxX() - 20) - _goolRect.getMinX()), _goolRect.getMidY()));
					if (_yoshida.size() == 0)
					{
						_kusahayasu->goResult();
					}
				});
				auto seq = Sequence::create(dilay, func, nullptr);
				runAction(seq);
				isHit = true;
			}

			if (isHit)continue;

			//enemyと当たっていますか
			for (auto enemy : _enemyManager->_enemyArr)
			{
				Rect enemyRect = enemy->getBoundingBox();
				if (targetRect.intersectsRect(enemyRect))
				{
					_effectManager->watageBakusan(_yoshida.at(target)->getPosition());

					_yoshida.at(target)->removeFromParentAndCleanup(true);
					_yoshida.erase(_yoshida.begin() + target);
					yosidaLiveingCheck();
					isHit = true;
					break;
				}
			}
			if (isHit)break;

			//死んだ吉田拓郎と当たっていますか
			for (auto kusa : shinikusa)
			{
				Rect kusaRect = kusa->getBoundingBox();
				Vec2 kusaOyaPos = kusa->getParent()->getPosition();
				Vec2 kusaPos = Vec2(kusaRect.getMinX(), kusaRect.getMinY()) + kusaOyaPos;
				kusaRect = Rect(kusaPos.x, kusaPos.y, kusaRect.size.width, kusaRect.size.height);
				if (targetRect.intersectsRect(kusaRect))
				{
					//u m s h
					float kyori = 1000;
					//右辺(-1.0)左辺(1,0)上辺(0,-1)下辺(0,1)
					Vec2 targetPos = _yoshida.at(target)->getPosition();
					Vec2 nextTargetPos = Vec2::ZERO;
					Vec2 houkou = Vec2::ZERO;

					if (targetRect.getMinY() <= kusaRect.getMaxY() &&			//上
						kyori >= kusaRect.getMaxY() - targetRect.getMinY() &&
						kusa->getTag() == 0)
					{
						houkou = Vec2(0, -1);
						kyori = kusaRect.getMaxY() - targetRect.getMinY();
						nextTargetPos = Vec2(targetPos.x, targetPos.y + kyori);
						isHit = true;
					}

					if (targetRect.getMinX() <= kusaRect.getMaxX() &&			//右
						kyori >= kusaRect.getMaxX() - targetRect.getMinX() &&
						kusa->getTag() == 1)
					{
						houkou = Vec2(-1, 0);
						kyori = kusaRect.getMaxX() - targetRect.getMinX();
						nextTargetPos = Vec2(targetPos.x + kyori, targetPos.y);
						isHit = true;
					}

					if (targetRect.getMaxY() >= kusaRect.getMinY() &&			//下
						kyori >= targetRect.getMaxY() - kusaRect.getMinY() &&
						kusa->getTag() == 2)
					{
						houkou = Vec2(0, 1);
						kyori = targetRect.getMaxY() - kusaRect.getMinY();
						nextTargetPos = Vec2(targetPos.x, targetPos.y - kyori);
						isHit = true;
					}

					if (targetRect.getMaxX() >= kusaRect.getMinX() &&			//左
						kyori >= targetRect.getMaxX() - kusaRect.getMinX())
					{
						houkou = Vec2(1, 0);
						kyori = targetRect.getMaxX() - kusaRect.getMinX();
						nextTargetPos = Vec2(targetPos.x - kyori, targetPos.y);
						isHit = true;
					}
					if (isHit)
					{
						_yoshida.at(target)->setPosition(nextTargetPos);
						_kusahayasu->kusaHaneAction(kusa, houkou, _yoshida.at(target));
						break;
					}
				}
			}

			if (isHit)continue;

			//障害物と当たっているか
			for (auto syougaibutu : _syougaibutu)
			{
				Rect syougaiRect = syougaibutu->getBoundingBox();
				Size syougaiSize = Size(syougaiRect.size.width, syougaiRect.size.height);
				syougaiRect = Rect{ syougaiRect.getMinX() + syougaiSize.width * 0.05f,
					syougaiRect.getMinY(),
					syougaiSize.width - syougaiSize.width * 0.1f,
					syougaiSize.height + 5 };

				if (targetRect.intersectsRect(syougaiRect))
				{

					int angleNum = 0;
					float kyori = 100000;

					if (targetRect.getMinY() <= syougaiRect.getMaxY() &&			//上
						kyori >= syougaiRect.getMaxY() - targetRect.getMinY())
					{
						angleNum = 0;
						kyori = syougaiRect.getMaxY() - targetRect.getMinY();
					}

					if (targetRect.getMinX() <= syougaiRect.getMaxX() &&			//右
						kyori >= syougaiRect.getMaxX() - targetRect.getMinX())
					{
						angleNum = 1;
						kyori = syougaiRect.getMaxX() - targetRect.getMinX();
					}

					if (targetRect.getMaxY() >= syougaiRect.getMinY() &&			//下
						kyori >= targetRect.getMaxY() - syougaiRect.getMinY())
					{
						angleNum = 2;
						kyori = targetRect.getMaxY() - syougaiRect.getMinY();
					}

					if (targetRect.getMaxX() >= syougaiRect.getMinX() &&			//左
						kyori >= targetRect.getMaxX() - syougaiRect.getMinX())
					{
						angleNum = 3;
						kyori = targetRect.getMaxX() - syougaiRect.getMinX();
					}

					_effectManager->watageBakusan(_yoshida.at(target)->getPosition());
					_kusahayasu->shiniHayasu(_yoshida.at(target)->getPosition(), angleNum, syougaibutu);
					_yoshida.at(target)->removeFromParentAndCleanup(true);
					_yoshida.erase(_yoshida.begin() + target);
					yosidaLiveingCheck();
					isHit = true;
					break;
				}
			}
			if (isHit)break;
			if (_yoshida.at(target)->_isWind)continue;
			//ほかの吉田と当たっているか
			for (int ather = 0; ather < _yoshida.size() - target; ather++)
			{
				if (target == ather || _yoshida.at(ather)->_isHit)continue;
				Rect atherRect = _yoshida.at(ather)->getBoundingBox();
				atherRect = Rect{
					atherRect.getMinX() + yoshidaSize*0.5f,
					atherRect.getMinY() + yoshidaSize*0.3f,
					yoshidaSize*0.2f,
					yoshidaSize*0.2f };

				if (targetRect.intersectsRect(atherRect))
				{
					//Vec2 movePos = Vec2(_yoshida.at(target)->getPosition() - _yoshida.at(ather)->getPosition());
					Vec2 movePos = Vec2::ZERO;
					if (targetRect.getMinX() >= atherRect.getMinX())movePos.x = _yoshida.at(ather)->getPositionX() + targetRect.size.width;
					else											movePos.x = _yoshida.at(ather)->getPositionX() - targetRect.size.width;
					if (targetRect.getMinY() >= atherRect.getMinY())movePos.y = _yoshida.at(ather)->getPositionY() + targetRect.size.height;
					else											movePos.y = _yoshida.at(ather)->getPositionY() + targetRect.size.height;
					_yoshida.at(target)->hitAction(movePos);
					break;
				}
			}
		}
	}
}

void YoshidasanNoManager::kazeKeisan()
{
	for (int i = 0; i < _yoshida.size(); i++)
	{
		float yoshidaAngle = atan2(_yoshida.at(i)->getPositionY() - _touchStartPos.y, _yoshida.at(i)->getPositionX() - _touchStartPos.x)* 180.0f / M_PI;
		yoshidaAngle += yoshidaAngle > 0 ? 0 : 360;
		if (_haniAngle >= fabs(_kumomoAngle - yoshidaAngle))
		{
			_yoshida.at(i)->vecKeisan(_touchStartPos, _windRange * (_windMaxTime - _windCallCnt) / _windMaxTime, _windCallCnt);
		}
	}
}

void YoshidasanNoManager::yoshidaCenterCall()
{
	_yoshidaCenterPos = Vec2(0, 0);
	Vec2 sinkou = _yoshidaCamera->getPosition();
	float torima = 0;
	for (int i = 0; i < _yoshida.size(); i++)
	{
		_yoshidaCenterPos += _yoshida.at(i)->getPosition();
	}

	for (int i = 0; i < _yoshida.size(); i++)
	{
		Vec2 yoshidaPos = _yoshida.at(i)->getPosition();
		if (yoshidaPos.x < (sinkou.x - designResolutionSize.width / 2 - 20))
		{
			_effectManager->watageBakusan(_yoshida.at(i)->getPosition());
			_yoshida.at(i)->stopAllActions();
			_yoshida.at(i)->removeFromParentAndCleanup(true);
			_yoshida.erase(_yoshida.begin() + i);
			if (_yoshida.size() == 0)
			{
				_kusahayasu->reStart();
			}
		}
	}
	_yoshidaCenterPos = _yoshidaCenterPos / _yoshida.size();
	_yoshidaCamera->_yoshidaCenterPos = _yoshidaCenterPos;
}

void YoshidasanNoManager::yoshidaWatashi()
{
	_enemyManager->_yoshidaArr = _yoshida;
}

void YoshidasanNoManager::yoshidaBorn(Vec2 targetPos)
{
	/*maxSpeed *= 0.8f;
	auto jump = JumpBy::create(
		1.0f,        
		Vec2(0, 150),
		200.0f,
		1
		);
	auto grow = ScaleTo::create(3.0f, 0.15f);
	auto seq = Sequence::create(jump, grow, nullptr);
	yoshida->runAction(seq);*/

}


float YoshidasanNoManager::getMaxRange()
{
	return _windMaxRange;
}
