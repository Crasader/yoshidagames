#include "Kusahayasu.h"

Kusahayasu * Kusahayasu::create()
{


	Kusahayasu *pRet = new Kusahayasu();
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

bool Kusahayasu::init()
{
	if (!Node::init())return false;

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadEffect("Pon.mp3");

	_score = 0;

	 _goalYoshida = 0;
	 _goalGirl = 0;
	 _goalDebu = 0;
	 _goalYanki = 0;

	 _isChangeScene = false;

	_kusa.clear();
	this->scheduleUpdate();
	return true;
}

void Kusahayasu::update(float dt)
{

}

void Kusahayasu::kusahayasu(Vec2 hayasuPos, int hayasuNam)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Pon.mp3");
	Sprite * kusa;
	if (hayasuNam == 0)
	{
		kusa = Sprite::create("pix/stageSozai/hana.png");
		kusa->setAnchorPoint(Vec2(0.5f, 1.0f));
	}

	else
	{
		kusa = Sprite::create("pix/stageSozai/zasou.png");
		kusa->setAnchorPoint(Vec2(0.5f, 1.0f));
	}
	
	addChild(kusa);
	kusa->setPosition(hayasuPos);
	_kusa.push_back(kusa);
	
	if (hayasuNam == 0)
	{
		auto up = MoveBy::create(1.0f, Vec2(0, kusa->getBoundingBox().size.height));
		auto eas = EaseOut::create(up, 3);
		kusa->runAction(eas);
	}
}

void Kusahayasu::scorePlus(int myNum)
{
	switch (myNum)
	{
	case 0:
		_goalYoshida++;
		break;
	case 1:
		_goalGirl++;
		break;
	case 2:
		_goalDebu++;
		break;
	case 3:
		_goalYanki++;
		break;
	default:
		break;
	}
	_score++;
}

void Kusahayasu::goResult()
{
	if (!_isChangeScene) {
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ResultScene::createScene(_goalYoshida, _goalGirl, _goalDebu, _goalYanki)));
		_isChangeScene = true;
	}
}
