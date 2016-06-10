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
	setTextureRect(Rect(100, 100, 100, 100));

	_isWind = false;

	_speed = Vec2(0, 0);

	Vec2 windmillPos = getPosition();

	Sprite* gate = Sprite::create();
	gate->setAnchorPoint(Vec2(0.0f, 0.0f));
	gate->setTextureRect(Rect(0, 0, 100, 200));
	gate->setPosition(Vec2(windmillPos.x,windmillPos.y + getBoundingBox().size.height));
	addChild(gate);

	this->scheduleUpdate();
	return false;
}

void Windmill::update(float dt)
{
	if (_isWind) 
	{
		windHitRotation();
	}
}

void Windmill::windHitRotation() 
{
	setRotation(getRotation()+10);
}

void Windmill::windHitMoveing(Node target) 
{
	
}

void Windmill::windSet(bool isWind, Vec2 speed) 
{
	_isWind = isWind;
	_speed = speed;
}

void Windmill::windStop() 
{
	_isWind = false;
	_speed = 0;
}