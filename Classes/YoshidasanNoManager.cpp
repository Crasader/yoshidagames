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
	int yoshidaSuu = 10;

	_goolRect = _stageCrater->getGoolRect();

	//吉田さんの生成
	for (int i = 0; i < yoshidaSuu; i++)
	{
		const char * yoshidaPas;
		int r = rand() % 4;
		//吉田のステ
		bool yankiCheck = false;
		float gravity = -0.5f;
		int maxSpeed = 10;
		int myNo = 0;

		switch (r)
		{
		case 0://いつもの
			yoshidaPas = "pix/actor/yoshidasan.png";
			gravity = -0.98f;
			maxSpeed = 10;
			myNo = 0;
			break;
		case 1://女
			yoshidaPas = "pix/actor/yoshidagirl.png";
			gravity = -0.8f;
			maxSpeed = 12;
			myNo = 1;
			break;
		case 2://でぶ
			yoshidaPas = "pix/actor/yoshidadebu.png";
			gravity = -1.1f;
			maxSpeed = 6;
			myNo = 2;
			break;
		case 3://ヤンキー
			yoshidaPas = "pix/actor/yoshidasanyanki.png";
			gravity = -0.98f;
			maxSpeed = 8;
			yankiCheck = true;
			myNo = 3;
			break;
		default://保険
			yoshidaPas = "pix/actor/yoshidasan.png";
			gravity = -0.5f;
			maxSpeed = 10;
			myNo = 0;
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

	_touchSP = Sprite::create("pix/Title/kumomo.png");
	_touchSP->setScale(0.2f);
	addChild(_touchSP);

	_yajirushiSP = Sprite::create("pix/eff/yajirushiYoko.png");
	_yajirushiSP->setScale(0.3);
	addChild(_yajirushiSP);

	_yajirushiPos = Vec2(_touchSP->getPosition());
	_touchAngle = 0.0;

	//touchしているか
	_isTouch = true;

	//touchしている場所
	_touchPos = Vec2(0, 0);

	//当たった時に渡すスピードの割合 speed/_speedtyousei
	_speedtyousei = 4.0f;

	//ゴーールした吉田の数
	_goolYoshidaNum = 0;

	_syougaibutu = _stageCrater->getSyougaibutu();

	_touchStartPos = Vec2::ZERO;
	_touchEndPos = Vec2::ZERO;

	_yoshidaCenter = Vec2(0, 0);

	_yoshidaCenterPos = Vec2(0, 0);

	_kumomoAngle = 0;

	_taisyouYoshida.clear();


	// updateを毎フレーム実行するように登録する
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
	if (!_isTouch)kazeKeisan();
	yoshidaNoAtarihantei();
}

void YoshidasanNoManager::touchCall(Vec2 touchPos, bool isTouch)
{
	_touchSP->setRotation(atan2( _touchStartPos.y - touchPos.y, touchPos.x - _touchStartPos.x) * 180 / M_PI);

	_touchAngle = (atan2(_touchStartPos.y - touchPos.y, touchPos.x - _touchStartPos.x) * 180 / M_PI);

	_yajirushiPos = Vec2(touchPos.x - _touchStartPos.x, touchPos.y - _touchStartPos.y);
}

void YoshidasanNoManager::touchStateCall(Vec2 touchPos)
{
	_touchStartPos = touchPos;
	_touchSP->setPosition(touchPos);
	_isTouch = true;
}

void YoshidasanNoManager::touchEndCall(Vec2 touchPos)
{
	_touchEndPos = touchPos;
	_isTouch = false;

	_effectManager->kazeNagareru(_touchStartPos, _touchEndPos, _touchAngle);
}

void YoshidasanNoManager::yosidaLiveingCheck()
{
	if (_yoshida.size() == 0)
	{
		_kusahayasu->goResult();
	}
}

void YoshidasanNoManager::yoshidaNoAtarihantei()
{
	vector<Sprite*> shinikusa = _kusahayasu->getShinikusa();

	for (int target = 0; target < _yoshida.size(); target++)
	{
		if (!_yoshida.at(target)->_isGool)
		{
			Rect targetRect = _yoshida.at(target)->getBoundingBox();
			float yoshidaSize = targetRect.size.width;
			//_effectManager->creatKirakira(_yoshida.at(target)->getPosition());
			targetRect = Rect{
				targetRect.getMinX() + yoshidaSize*0.45f,
				targetRect.getMinY() + yoshidaSize*0.25f,
				yoshidaSize*0.40f,
				yoshidaSize*0.40f };

			//ごーると当たっているか
			if (targetRect.intersectsRect(_goolRect))//&& !_yoshida.at(target)->_isGool
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
				break;
			}

			//死んだ吉田拓郎と当たっていますか
			for (int i = 0; i < shinikusa.size(); i++)
			{
				Rect kusaRect = shinikusa[i]->getBoundingBox();
				if (targetRect.intersectsRect(kusaRect) && !_yoshida.at(target)->_isGool)
				{
					float angle = atan2(
						_yoshida.at(target)->getPositionY() - kusaRect.getMidY(),
						_yoshida.at(target)->getPositionX() - kusaRect.getMidX())
						* 180 / M_PI;
					//右辺(-1.0)左辺(1,0)上辺(0.-1)下辺(0.1)
					if (45 < angle && angle < 135 && _yoshida.at(target)->_isGoDown)
					{
						_yoshida.at(target)->setPositionY(kusaRect.getMaxY());
						_kusahayasu->kusaHaneAction(shinikusa[i], Vec2(0, -1));
						break;
					}
					else if (135 < angle && angle < 180 || -180 < angle && angle < -135 && _yoshida.at(target)->_isGoRight)
					{
						_yoshida.at(target)->setPositionX(kusaRect.getMinX());
						_kusahayasu->kusaHaneAction(shinikusa[i], Vec2(1, 0));
						break;
					}
					else if (-135 < angle && angle < -45 && !(_yoshida.at(target)->_isGoDown))
					{
						_yoshida.at(target)->setPositionY(kusaRect.getMinY());
						_kusahayasu->kusaHaneAction(shinikusa[i], Vec2(0, 1));
						break;
					}
					else if (-45 < angle && angle < 45 && !(_yoshida.at(target)->_isGoRight))
					{
						_yoshida.at(target)->setPositionX(kusaRect.getMaxX());
						_kusahayasu->kusaHaneAction(shinikusa[i], Vec2(-1, 0));
						break;
					}
				}
			}

			//障害物と当たっているか
			for (int i = 0; i < _syougaibutu.size(); i++)
			{
				Rect syougaiRect = _syougaibutu[i]->getBoundingBox();
				Size syougaiSize = Size(syougaiRect.size.width, syougaiRect.size.height);
				syougaiRect = Rect{ syougaiRect.getMinX() + syougaiSize.width * 0.05f,
					syougaiRect.getMinY(),
					syougaiSize.width - syougaiSize.width * 0.1f,
					syougaiSize.height + 5 };

				if (targetRect.intersectsRect(syougaiRect))
				{
					float angle = atan2(
						_yoshida.at(target)->getPositionY() - syougaiRect.getMidY(),
						_yoshida.at(target)->getPositionX() - syougaiRect.getMidX())
						* 180 / M_PI;
					int angleNum = 0;
					log("%f", angle);
					if (45 < angle && angle < 135)angleNum = 0;
					else if (135 < angle && angle < 180 || -180 < angle && angle < -135)angleNum = 3;
					else if (-135 < angle && angle < -45)angleNum = 2;
					else if (-45 < angle && angle < 45)angleNum = 1;
					_effectManager->watageBakusan(_yoshida.at(target)->getPosition());
					_kusahayasu->shiniHayasu(_yoshida.at(target)->getPosition(), angleNum);

					_yoshida.at(target)->removeFromParentAndCleanup(true);
					_yoshida.erase(_yoshida.begin() + target);
					yosidaLiveingCheck();
					break;
				}

			}

			//ほかの吉田と当たっているか
			for (int ather = 0; ather < _yoshida.size() - target; ather++)
			{
				if (target == ather)continue;
				Rect atherRect = _yoshida.at(ather)->getBoundingBox();
				atherRect = Rect{
					atherRect.getMinX() + yoshidaSize*0.5f,
					atherRect.getMinY() + yoshidaSize*0.3f,
					yoshidaSize*0.2f,
					yoshidaSize*0.2f };
				float targetVec = sqrt(
					pow(_touchPos.x - _yoshida.at(target)->getPositionX(), 2) +
					pow(_touchPos.y - _yoshida.at(target)->getPositionY(), 2));

				if (targetRect.intersectsRect(atherRect))
				{
					float atherVec = sqrt(
						pow(_touchPos.x - _yoshida.at(ather)->getPositionX(), 2) +
						pow(_touchPos.y - _yoshida.at(ather)->getPositionY(), 2));
					if (targetVec >= atherVec)
					{
						Vec2 atherSpeed = _yoshida.at(ather)->getSpeed();
						_yoshida.at(ather)->speedChange(-atherSpeed / _speedtyousei);
						_yoshida.at(target)->speedChange(Vec2(atherSpeed.x / _speedtyousei, 0));
					}
					if (targetVec < atherVec)
					{
						Vec2 targetSpeed = _yoshida.at(target)->getSpeed();
						_yoshida.at(ather)->speedChange(Vec2(targetSpeed.x / _speedtyousei, 0));
						_yoshida.at(target)->speedChange(-targetSpeed / _speedtyousei);
					}
				}
			}
		}
	}
}

void YoshidasanNoManager::kazeKeisan()
{
	int hanniAngle = 30;
	_taisyouYoshida.clear();

	//タッチしはじめと終わりのベクトルから角度を算出（右から上でひだりまでに0~+180,右から下で左までに0~-180）
	float angle = atan2(_touchEndPos.y - _touchStartPos.y, _touchEndPos.x - _touchStartPos.x) * 180.0f / M_PI;
	_kumomoAngle = angle;

	//左ギリギリ上
	if (angle > 180 - hanniAngle)
	{
		float overAngle = hanniAngle - 180 + angle;

		for (int i = 0; i < _yoshida.size(); i++)
		{
			float yoshidaAngle = atan2(_yoshida.at(i)->getPositionY() - _touchStartPos.y, _yoshida.at(i)->getPositionX() - _touchStartPos.x)* 180.0f / M_PI;

			if ((yoshidaAngle >= angle - hanniAngle && yoshidaAngle <= angle + hanniAngle) ||
				(yoshidaAngle <= -180.0f + overAngle && yoshidaAngle >= -180.0f))
			{

				_taisyouYoshida.push_back(i);
			}
		}
	}

	//左ギリギリ下
	else if (angle < -180 + hanniAngle)
	{


		float overAngle = -hanniAngle + 180 + angle;

		for (int i = 0; i < _yoshida.size(); i++)
		{
			float yoshidaAngle = atan2(_yoshida.at(i)->getPositionY() - _touchStartPos.y, _yoshida.at(i)->getPositionX() - _touchStartPos.x)* 180.0f / M_PI;
			if ((yoshidaAngle >= angle - hanniAngle && yoshidaAngle <= angle + hanniAngle) ||
				(yoshidaAngle >= 180.0f + overAngle && yoshidaAngle <= 180.0f))
			{
				_taisyouYoshida.push_back(i);
			}
		}
	}

	//その他
	else
	{
		for (int i = 0; i < _yoshida.size(); i++)
		{
			float yoshidaAngle = atan2(_yoshida.at(i)->getPositionY() - _touchStartPos.y, _yoshida.at(i)->getPositionX() - _touchStartPos.x)* 180.0f / M_PI;
			if (yoshidaAngle >= angle - hanniAngle && yoshidaAngle <= angle + hanniAngle)
			{
				_taisyouYoshida.push_back(i);
			}
		}
	}



	for (int i = 0; i < _taisyouYoshida.size(); i++)
	{
		_yoshida.at(_taisyouYoshida[i])->vecKeisan(_touchStartPos);
	}

}

void YoshidasanNoManager::yoshidaCenterCall()
{
	_yoshidaCenter = Vec2(0, 0);
	Vec2 sinkou = _yoshidaCamera->getPosition();
	float torima = 0;
	for (int i = 0; i < _yoshida.size(); i++)
	{
		_yoshidaCenter += _yoshida.at(i)->getPosition();
	}

	for (int i = 0; i < _yoshida.size(); i++)
	{
		Vec2 yoshidaPos = _yoshida.at(i)->getPosition();
		if (yoshidaPos.x < (sinkou.x - designResolutionSize.width / 2 - 50))
		{
			_effectManager->watageBakusan(_yoshida.at(i)->getPosition());
			_yoshida.at(i)->removeFromParentAndCleanup(true);
			_yoshida.erase(_yoshida.begin() + i);
			if (_yoshida.size() == 0)
			{
				_kusahayasu->goResult();
			}
		}
	}
	_yoshidaCenter = _yoshidaCenter / _yoshida.size();
	//_yoshidaCamera->setPosition(_yoshidaCenter);
}

void YoshidasanNoManager::yajirushiSet()
{
	Vec2 kumoPos = _touchSP->getPosition();
	_yajirushiSP->setRotation(_touchAngle);
	float radians = _touchAngle * M_PI / 180.0f;
	float x = cos(radians);
	float y = sin(radians);
	_yajirushiSP->setPosition(kumoPos + Vec2(x,y));
}