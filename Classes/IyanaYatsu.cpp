#include "IyanaYatsu.h"

IyanaYatsu * IyanaYatsu::create(Vec2 bornPos)
{
	IyanaYatsu *pRet = new IyanaYatsu();
	if (pRet && pRet->init(bornPos))
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

bool IyanaYatsu::init(Vec2 bornPos)
{
	if(!Node::init())return false;

	float iyanaScale = 0.7f;
	_body = Sprite::create("pix/actor/doukumomoB.png");
	addChild(_body);
	_body->setAnchorPoint(Vec2(0.5f, 0));
	_body->setPosition(bornPos);
	_body->setScale(iyanaScale);

	_head = Sprite::create("pix/actor/dokukumomoA.png");
	addChild(_head);
	_head->setAnchorPoint(Vec2(0.5f, 0.1f));
	_head->setPosition(Vec2(_body->getBoundingBox().getMidX(),_body->getBoundingBox().getMaxY() - 0));
	_head->setScale(iyanaScale);
	_head->setFlipX(true);

	this->scheduleUpdate();
	return true;
}

void IyanaYatsu::update(float dt)
{
}

void IyanaYatsu::headRotateSet(float rotate)
{
	_head->setRotation(rotate);
}

void IyanaYatsu::kazehukasu(Vector<Yoshidasan*> yoshida)
{
	float windRange = 300.0f;
	Vector<Yoshidasan*> taisyouyoshida;
	for (auto yoshi : yoshida) 
	{
		float angle = atan2(yoshi->getPositionY() - _head->getPositionY(), yoshi->getPositionY() - _head->getPositionX()) * 180 / M_PI ;
		if (angle > 20 && angle < 90) 
		{
			float kyori = sqrt(pow(yoshi->getPositionX() - _head->getPositionX(), 2) + pow(yoshi->getPositionY() - _head->getPositionY(), 2));
			if (windRange > kyori)
			{
				taisyouyoshida.pushBack(yoshi);
			}
		}
	}
	for (auto yoshi : taisyouyoshida)
	{
		yoshi->vecKeisan(_head->getPosition(), windRange, 1);
	}
}
