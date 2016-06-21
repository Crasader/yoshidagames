#include "Item.h"

Item *Item::create()
{

	Item *pRet = new Item();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Item::init()
{
	//速度
	_speed = Vec2(0, 0);
	//重力の値
	_gSpeed = -1.6;
	//右向きに向かっているか
	_isGoRight = true;
	//下向きに向かっているか
	_isGoDown = true;
	//風に当たっているかどうか
	_isWind = false;
	//最大移動速度
	_maxSpeed = 20;

	_windBoost = 1.0f;

	//ステージ内での最大移動量（X方向）
	_moveMaxX = (designResolutionSize.width * 2) - 100;

	_rotCnt = 0;

	Vec2 ItemPos = getPosition();

	this->scheduleUpdate();
	return false;
}

void Item::update(float dt)
{
	windSpeedDown();

	if (_isWind)
	{
		windHitMoveing();
	}
}

void Item::windHitMoveing()
{

}

void Item::windSet(bool isWind, Vec2 speed)
{
	_isWind = isWind;
	_speed = speed;
}

void Item::windStop()
{
	_isWind = false;
	_speed = Vec2(0, 0);
}

void Item::windSpeedDown()
{
	if (_speed.x > 0) _speed.x -= 0.05;
	if (_speed.x < 0) _speed.x += 0.05;
	if (_speed.y > 0) _speed.y -= 0.05;
	if (_speed.y < 0) _speed.y += 0.05;
}

//風からの移動量の計算
void Item::vecKeisan(Vec2 touchPos, float windRange, float windBoost, float actionTime)
{
	//実際移動量
	float vecPulus = 0.0f;
	//適用範囲
	float hani = windRange;

	_windBoost = windBoost;

	//移動値の計算
	if ((sqrt(
		pow(touchPos.x - getPositionX(), 2) +
		pow(touchPos.y - getPositionY(), 2)))
		<= hani)
	{
		//if (!_isWind)kazekaiten(actionTime);
		//{
		vecPulus = _maxSpeed * _windBoost *
			(hani - (sqrt(
				pow(touchPos.x - getPositionX(), 2) +
				pow(touchPos.y - getPositionY(), 2))))
			/ hani;


		//角度の計算
		float angle = atan2(getPositionY() - touchPos.y, getPositionX() - touchPos.x);
		//移動量の適用
		_speed = Vec2(vecPulus * cos(angle), vecPulus * sin(angle));

	}

	//移動方向の変更X
	if (touchPos.x - getPositionX() <= 0)_isGoRight = true;
	else _isGoRight = false;

	//移動方向の変更Y
	if (touchPos.y - getPositionY() >= 0)_isGoDown = true;
	else _isGoDown = false;
	setNoOverMaxSpeed();
}

void Item::setNoOverMaxSpeed()
{

	//y方向-------------------------------------------------------------------

	if (!_isGoDown &&_speed.y >= _maxSpeed * _windBoost)//上向き
	{
		_speed.y = _maxSpeed * _windBoost;
	}

	else if (_isGoDown &&_speed.y <= -_maxSpeed * _windBoost)//下向き
	{
		_speed.y = -_maxSpeed * _windBoost;
	}
	//------------------------------------------------------------------------

	//x方向-------------------------------------------------------------------

	if (_isGoRight && _speed.x >= _maxSpeed * _windBoost)
	{
		_speed.x = _maxSpeed * _windBoost;
	}
	else if (!_isGoRight && _speed.x <= -_maxSpeed * _windBoost)
	{
		_speed.x = -_maxSpeed * _windBoost;
	}
}
