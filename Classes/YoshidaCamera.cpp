#include "YoshidaCamera.h"
#include "YoshidasanNoManager.h"

YoshidaCamera *YoshidaCamera::create()
{
	YoshidaCamera *pRet = new YoshidaCamera();
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

bool YoshidaCamera::init()
{
	if (!Sprite::init()) return false;

	Vec2 startPos = Vec2(designResolutionSize.width / 2, designResolutionSize.height / 2);

	this->setPosition(startPos);

	_isMoved = false;
	_speed = 0.3;
	_isScroll = false;

	_yoshidaCenterPos = Vec2(0, 0);

	scheduleUpdate();

	return true;
}

void YoshidaCamera::update(float dt) 
{
	if (_isMoved) 
	{
		scrollMove();
	}
}

void YoshidaCamera::scrollMove()
{
	Vec2 myPos = getPosition();
	myPos.x += _speed;
	if (myPos.x < _yoshidaCenterPos.x) 
	{
		myPos = _yoshidaCenterPos;
	}

	this->setPosition(myPos);
}