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
	initWithFile("pix/stageSozai/windmillA.png");
	setScale(0.8);

	_target = NULL;

	_isWind = false;

	_speed = Vec2(0, 0);

	_rotCnt = 0;

	Vec2 windmillPos = getPosition();

	this->scheduleUpdate();
	return false;
}

void Windmill::update(float dt)
{
	windSpeedDown();

	if (_isWind) 
	{
		windHitMoveing();
	}
}

void Windmill::windHitMoveing()
{
	windHitRotation();

	Vec2 targetPos = _target->getPosition();
	if (targetPos.y <= designResolutionSize.height*0.8)
	{
		_target->setPosition(Vec2(targetPos.x, targetPos.y + 0.5));
	}
}

void Windmill::windHitRotation()
{
	setRotation(getRotation() + _speed.x);
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