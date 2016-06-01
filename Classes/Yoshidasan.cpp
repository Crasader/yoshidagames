#include "Yoshidasan.h"
#include "YoshidasanNoManager.h"

bool Yoshidasan::init(const char *fileName, int maxSpeed, float gravity, bool isYanki, int myNo)
{
	if (!Sprite::init())return false;
	initWithFile(fileName);
	setScale(0.2f);
	//重力の値
	_gSpeed = gravity;
	//プレイヤーの速度
	_pSpeed = Vec2(0, _gSpeed);
	//右向きに向かっているか
	_isGoRight = true;
	//下向きに向かっているか
	_isGoDown = true;
	//タッチしているか	
	_isWind = false;
	//ゴールしたかどうか
	_isGool = false;
	//やんきーかどうか
	_isYanki = isYanki;
	//自分の番号(ナニ田さんなのかの番号)
	_myNo = myNo;
	//最大移動速度
	_maxSpeed = maxSpeed;

	//向きを変える処理を呼ぶクールタイム
	_fripCoolTime = 5.0f;
	//向きを変える処理を呼ぶクールタイムで使うカウント
	_fripCoolCnt = 0.0f;

	//ステージ内での最大移動量（X方向）
	_moveMaxX = (designResolutionSize.width * 2) - 100;

	// updateを毎フレーム実行するように登録する
	this->scheduleUpdate();

	return true;
}

void Yoshidasan::update(float dt)
{
	if (!_isGool)speedKeisan();
	if (_isWind)rotateKeisan();

	if (_fripCoolCnt > 0) 
	{
		_fripCoolCnt -= 0.1;
		if (_fripCoolCnt < 0) 
		{
			_fripCoolCnt = 0;
		}
	}
}

//風からの移動量の計算
void Yoshidasan::vecKeisan(Vec2 touchPos, float windRange)
{
	//風の強さ調整用
	float windTyousei = 2;
	//実際移動量
	float vecPulus = 0.0f;
	//適用範囲
	float hani = windRange;

	//移動値の計算
	if ((sqrt(
		pow(touchPos.x - getPositionX(), 2) +
		pow(touchPos.y - getPositionY(), 2)))
		<= hani)
	{

		vecPulus = _maxSpeed *
			(hani - (sqrt(
				pow(touchPos.x - getPositionX(), 2) +
				pow(touchPos.y - getPositionY(), 2))))
			/ hani;
	}

	//角度の計算
	float angle = atan2(getPositionY() - touchPos.y, getPositionX() - touchPos.x);
	//移動量の適用
	_pSpeed = Vec2(vecPulus * cos(angle) * windTyousei, vecPulus * sin(angle) * windTyousei);

	//移動方向の変更X
	if (touchPos.x - getPositionX() <= 0)_isGoRight = true;
	else _isGoRight = false;

	//移動方向の変更Y
	if (touchPos.y - getPositionY() >= 0)_isGoDown = true;
	else _isGoDown = false;

}

//当たった時のspeed値イドウ
void Yoshidasan::speedChange(Vec2 plusSpeed)
{
	_pSpeed.x += plusSpeed.x;
	_pSpeed.y += plusSpeed.y;
}

//speedの計算
void Yoshidasan::speedKeisan()
{
	//重力をスピードの減少にどの程度反映するか調整
	int p = 3;

	//y方向の運動量の計算-----------------------------------------------------
	if (!_isGoDown)	//下向き
	{
		if (_pSpeed.y > _gSpeed)
		{
			if (_pSpeed.y >= _maxSpeed)
			{
				_pSpeed.y = _maxSpeed;
			}
			_pSpeed.y += _gSpeed / p;
		}
		else
		{
			_pSpeed.y = _gSpeed;
			_isGoDown = true;
		}
	}
	else            //上向き
	{
		if (_pSpeed.y < _gSpeed)
		{
			if (_pSpeed.y <= -_maxSpeed)
			{
				_pSpeed.y = -_maxSpeed;
			}
			_pSpeed.y -= _gSpeed / p;
		}

		else
		{
			_pSpeed.y = _gSpeed;
		}
	}
	//------------------------------------------------------------------------

	//x方向の運動量の計算-----------------------------------------------------
	if (_pSpeed.x != 0)
	{
		if (_isGoRight)
		{
			if (_pSpeed.x > 0)
			{
				if (_pSpeed.x >= _maxSpeed)
				{
					_pSpeed.x = _maxSpeed;
				}
				_pSpeed.x += _gSpeed / p;
				_isWind = true;
			}
			else
			{
				_pSpeed.x = 0;
				_isWind = false;
				actionYuraYura();

			}
		}
		else
		{
			if (_pSpeed.x < 0)
			{
				if (_pSpeed.x <= -_maxSpeed)
				{
					_pSpeed.x = -_maxSpeed;
				}
				_pSpeed.x -= _gSpeed / p;
				_isWind = true;
			}
			else
			{
				_pSpeed.x = 0;
				_isWind = false;
				actionYuraYura();
			}
		}
	}
	//------------------------------------------------------------------------

	//移動量を加算してイドウ
	setPosition(Vec2(getPositionX() + _pSpeed.x, getPositionY() + _pSpeed.y));

	//画面端から１００以内にいるようにする---------------------------------------
	if (getPositionY() > designResolutionSize.height - 100)
	{
		setPositionY(designResolutionSize.height - 100);
	}
	if (getPositionY() < designResolutionSize.height * 0.16f)
	{
		setPositionY(designResolutionSize.height * 0.16f);
		allChangeReset();
	}
	if (getPositionX() > _moveMaxX)
	{
		setPositionX(_moveMaxX);
	}
	if (getPositionX() < 100)
	{
		setPositionX(100);
	}
	//--------------------------------------------------------------------------

}

//rotateの計算
void Yoshidasan::rotateKeisan()
{
	if (_fripCoolCnt == 0) 
	{
		//自分の角度をspeedのベクトルから計算して適用　度 = ラジアン × 180 ÷ 円周率 + 90
		setRotation((atan2(_pSpeed.y, _pSpeed.x) * 180.0f / M_PI) + 90);
		bool xBool = false;
		if (_isYanki) xBool = _isGoRight == _isGoDown;
		else xBool = _isGoRight != _isGoDown;
		_fripCoolCnt = _fripCoolTime;
		setFlipX(xBool);
		setFlipY(!_isGoDown);
	}
}

//speedを調べる
Vec2 Yoshidasan::getSpeed()
{
	return _pSpeed;
}

//いつもの揺れ
void Yoshidasan::actionYuraYura()
{
	stopAllActions();
		_fripCoolCnt = _fripCoolTime;
		setFlipY(false);
		setFlipX(false);
	auto modosu = RotateTo::create(0.5f, 0);
	auto func = CallFunc::create([=]()
	{
		auto yuraR = RotateBy::create(0.8f, 30);
		auto easeYuraR = EaseInOut::create(yuraR, 2);
		auto yuraL = RotateBy::create(0.8f, -30);
		auto easeYuraL = EaseInOut::create(yuraL, 2);
		auto yura = Sequence::create(easeYuraR, easeYuraL, nullptr);
		auto yurayura = RepeatForever::create(yura);
		runAction(yurayura);
	});
	auto sequence = Sequence::create(modosu, func, nullptr);
	runAction(sequence);

}

//始めの飛び出し
void Yoshidasan::startGo(Vec2 moveState, float dilayTime)
{
	stopAllActions();
	auto  delay = DelayTime::create(dilayTime);
	auto move = MoveBy::create(0.3f, moveState);
	auto func = CallFunc::create([=]()
	{
		actionYuraYura();
	});
	auto sequence = Sequence::create(delay, move, func, nullptr);
	runAction(sequence);

}

//葉っぱジャンプ！
void Yoshidasan::happaPiyon(Vec2 muki)
{
	stopAllActions();
	_isGool = true;
	float actionTime = 0.1f;
	int moveKyori = 50;
	auto move = MoveBy::create(actionTime, muki * moveKyori);
	auto moveEI = EaseIn::create(move, 3);
	auto owari = CCCallFunc::create([=]()
	{
		_isGool = false;
		actionYuraYura();
	});
	auto seq = Sequence::create(moveEI, owari, nullptr);
	runAction(seq);

}

//変化を戻す
void Yoshidasan::allChangeReset()
{
	stopAllActions();
		setFlipY(false);
		setFlipX(false);
		setRotation(0);
}

//ゴールした時の処理
void Yoshidasan::actionGoolMove(Vec2 centerPos, float dilayTime)
{
	if (!_isGool)
	{
		allChangeReset();
		_isGool = true;
		auto junp = JumpTo::create(dilayTime, centerPos, 100, 1);
		auto kaiten = RotateTo::create(dilayTime, 180.0f);
		auto spw = Spawn::create(junp, kaiten, nullptr);
		auto desu = CallFunc::create([=]()
		{
			YoshidasanNoManager *manager = (YoshidasanNoManager*)getParent();
			manager->yosidaLiveingCheck();
			removeFromParentAndCleanup(true);
		});
		auto seq = Sequence::create(spw, desu, nullptr);
		runAction(seq);
	}
}

//speedを反転
void Yoshidasan::speedFlip()
{
	_pSpeed = -_pSpeed;
	_isGoDown != _isGoDown;
	_isGoRight != _isGoRight;
}

