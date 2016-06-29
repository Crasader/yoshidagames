#include "Windmill.h"

Windmill * Windmill::create()
{

	Windmill *pRet = new Windmill();
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

bool Windmill::init()
{
	if (!Item::init())return false;
	initWithFile("pix/stageSozai/windmillA.png");
	setScale(0.8);

	//_target = NULL;

	_isWind = false;

	_speed = Vec2(0, 0);

	_rotCnt = 0;

	_startPos = _target->getPosition();

	this->scheduleUpdate();
	return true;
}

void Windmill::update(float dt)
{
	windSpeedDown();
	windHitRotation();
}

void Windmill::windHitMoveing(float num)
{
	Vec2 targetPos = _target->getPosition();

	if (targetPos.y > designResolutionSize.height*0.8)
	{
		targetPos.y = designResolutionSize.height*0.8;
	}

	if (targetPos.y < _startPos.y)
	{
		targetPos.y = _startPos.y;
	}

	if (targetPos.y <= designResolutionSize.height*0.8 && targetPos.y >= _startPos.y)
	{
		_target->setPosition(Vec2(targetPos.x, targetPos.y + 1.0 * num));
	}
}

void Windmill::windHitRotation()
{
	setRotation(getRotation() + _speed.x*3);
	
	_rotCnt += +_speed.x * 3;
	if (_rotCnt > 5)
	{
		windHitMoveing(1);
		_rotCnt = 0;
	}
	if (_rotCnt < -5) 
	{
		windHitMoveing(-1);
		_rotCnt = 0;
	}
	
}



//void Windmill::windSet(bool isWind, Vec2 speed) 
//{
//	_isWind = isWind;
//	_speed = speed;
//}

//void Windmill::windStop() 
//{
//	_isWind = false;
//	_speed = Vec2(0,0);
//}

//void Windmill::windSpeedDown() 
//{
//	if (_speed.x > 0) _speed.x -= 0.05;
//	if (_speed.x < 0) _speed.x += 0.05;
//	if (_speed.y > 0) _speed.y -= 0.05;
//	if (_speed.y < 0) _speed.y += 0.05;
//}