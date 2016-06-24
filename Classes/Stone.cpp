#include "Stone.h"

Stone * Stone::create()
{

	Stone *pRet = new Stone();
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

bool Stone::init()
{

	initWithFile("pix/stageSozai/stone.png");
	setTextureRect(Rect(100, 100, 50, 50));

	_isWind = false;

	_speed = Vec2(0, 0);

	_rotCnt = 0;

	Vec2 StonePos = getPosition();

	this->scheduleUpdate();
	return false;
}

void Stone::update(float dt)
{
	windSpeedDown();

	if (_isWind)
	{
		windHitMoveing();
	}
}

void Stone::windHitRotation()
{
	setRotation(getRotation() + _speed.x);
}

void Stone::windHitMoveing()
{
	windHitRotation();
}