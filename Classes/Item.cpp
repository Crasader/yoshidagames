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

	_isWind = false;

	_speed = Vec2(0, 0);

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