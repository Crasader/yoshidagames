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
	initWithFile("pix/stageSozai/stone.png");
	setTextureRect(Rect(100, 100, 50, 50));

	_target = NULL;

	_isWind = false;

	_speed = Vec2(0, 0);

	_rotCnt = 0;

	Vec2 windmillPos = getPosition();

	Sprite* gate1 = Sprite::create();
	gate1->setAnchorPoint(Vec2(0.0f, 0.5f));
	gate1->setTextureRect(Rect(0, 0, 50, 300));
	gate1->setPosition(Vec2(windmillPos.x, windmillPos.y));//+ getBoundingBox().size.height));
	addChild(gate1);

	Sprite* gate2 = Sprite::create();
	gate2->setAnchorPoint(Vec2(0.5f, 0.5f));
	gate2->setTextureRect(Rect(0, 0, 300, 50));
	gate2->setPosition(Vec2(windmillPos.x, windmillPos.y));//+ getBoundingBox().size.height));
	addChild(gate2);

	this->scheduleUpdate();
	return false;
}

void Windmill::update(float dt)
{
	windSpeedDown();

	if (_isWind) 
	{
		windHitRotation();
	}
}

void Windmill::windHitRotation()
{
	setRotation(getRotation() + _speed.x);
	windHitMoveing();
}

void Windmill::windHitMoveing()
{
	Vec2 targetPos = _target->getPosition();
	if (targetPos.y <= designResolutionSize.height*0.8) 
	{
		_target->setPosition(Vec2(targetPos.x, targetPos.y+0.5));
	}
}

void Windmill::windSet(bool isWind, Vec2 speed) 
{
	_isWind = isWind;
	_speed = speed;
}

void Windmill::windStop() 
{
	_isWind = false;
	_speed = Vec2(0,0);
}

void Windmill::windSpeedDown() 
{
	if (_speed.x > 0) _speed.x -= 0.05;
	if (_speed.x < 0) _speed.x += 0.05;
	if (_speed.y > 0) _speed.y -= 0.05;
	if (_speed.y < 0) _speed.y += 0.05;
}