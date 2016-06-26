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
	if (!Item::init())return false;
	initWithFile("pix/stageSozai/stone.png");
	setTextureRect(Rect(100, 100, 50, 50));

	_isWind = false;

	_speed = Vec2(0, 0);

	_rotCnt = 0;

	Vec2 StonePos = getPosition();

	this->scheduleUpdate();
	return true;
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
	move();
}

void Stone::move()
{
	//ˆÚ“®—Ê‚ð‰ÁŽZ‚µ‚ÄƒCƒhƒE
	setPosition(Vec2(getPositionX() + _speed.x, getPositionY() + _speed.y));

	if (getPositionY() < designResolutionSize.height * 0.16f)
	{
		setPositionY(designResolutionSize.height * 0.16f);
		//allChangeReset();
	}
}