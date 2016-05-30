#include "Kumomo.h"



Kumomo * Kumomo::create()
{

		Kumomo *pRet = new Kumomo();
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

bool Kumomo::init()
{
	initWithFile("pix/Title/kumomo.png");
	setScale(0.2f);
	
	_touchStartPos = Vec2::ZERO;
	_touchEndPos = Vec2::ZERO;

	_isTouch = false;

	_yajirushiSP = Sprite::create("pix/eff/yajirushiYoko.png");
	_yajirushiSP->setPosition(500, 150);
	_yajirushiSP->setScale(0.8);
	addChild(_yajirushiSP);


	this->scheduleUpdate();
	return false;
}

void Kumomo::update(float dt)
{
}

void Kumomo::touchCall(Vec2 touchPos)
{
	_touchEndPos = touchPos;
	_yoshiMana->touchCall(touchPos, true);

	yajirushiSet();
}


void Kumomo::touchStartCall(Vec2 touchPos)
{
	_isTouch = true;
	setPosition(touchPos);
	_yoshiMana->touchCall(touchPos, true);
	_yoshiMana->touchStateCall(touchPos);
	_touchStartPos = touchPos;
	yajirushiSet();

}

void Kumomo::touchEndCall(Vec2 touchPos)
{
	_touchEndPos = touchPos;
	_isTouch = false;
	_yoshiMana->touchEndCall(touchPos);
	yajirushiSet();
}

void Kumomo::yajirushiSet()
{
	//�^�b�`���͂��߂ƏI���̃x�N�g������p�x���Z�o�i�E�����łЂ���܂ł�0~+180,�E���牺�ō��܂ł�0~-180�j
	float angle = atan2(_touchStartPos.y - _touchEndPos.y, _touchEndPos.x - _touchStartPos.x) * 180.0f / M_PI;
	setRotation(angle);
}
