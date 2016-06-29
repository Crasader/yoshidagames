#pragma execution_character_set("utf-8") 
#include "SelectScene.h"
#include "HelloWorldScene.h"

Scene *SelectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SelectScene::create();
	scene->addChild(layer);

	return scene;
}

SelectScene *SelectScene::create()
{
	SelectScene *pRet = new SelectScene();
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

bool SelectScene::init()
{
	if (!FLayer::init()) return false;

	Sprite *backGround = Sprite::create("pix/buck/stage.png");
	backGround->setAnchorPoint(Vec2(0.0f, 0.0f));
	backGround->setPosition(Vec2(0, 0));
	addChild(backGround);

	Sprite *ki = Sprite::create("pix/buck/ki.png");
	ki->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(ki);


	Sprite *jimen = Sprite::create("pix/stageSozai/ground.png");
	jimen->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(jimen, 5);

	_yoshida = Sprite::create("pix/actor/yoshidasan.png");
	addChild(_yoshida);
	_yoshida->setScale(0.3f);
	_yoshida->setPosition(Vec2(designResolutionSize.width * 0.5f, designResolutionSize.height * 0.7f));
	scheduleUpdate();


	_uekibati.clear();
	for (int i = 0; i < 3; i++)
	{
		Sprite *ueki = Sprite::create("pix/stageSozai/uekibati.png");
		addChild(ueki);
		ueki->setAnchorPoint(Vec2(0.0f, 0.0f));
		ueki->setPosition(Vec2(designResolutionSize.width*(0.1f + 0.3f * i),jimen->getBoundingBox().getMaxY() - 30));
		_uekibati.push_back(ueki);
	}
	
	
	_kumomo = Sprite::create("pix/Title/kumomo.png");
	addChild(_kumomo);
	_kumomo->setScale(0.4f);
	_kumomo->setVisible(false);

	_touchStartPos = Vec2::ZERO;

	return true;
}

void SelectScene::update(float delta)
{
	FLayer::update(delta);


}

bool SelectScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	FLayer::onTouchBegan(touch, event);
	Vec2 touchPos = touch->getLocation();
	_kumomo->setVisible(true);
	_kumomo->setPosition(touchPos);
	_touchStartPos = touchPos;
	_kumomo->setScale(0.4f);

	return true;
}

void SelectScene::onTouchMoved(Touch * touch, Event * event)
{
	FLayer::onTouchMoved(touch, event);
	Vec2 touchPos = touch->getLocation();
	float angle = atan2(_touchStartPos.y - touchPos.y, touchPos.x - _touchStartPos.x) * 180.0f / M_PI;
	_kumomo->setRotation(angle);


}

void SelectScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Vec2 touchPos = touch->getLocation();
	auto tizi = ScaleTo::create(0.2f, 0.2f);
	_kumomo->runAction(tizi);
	float yosiRange = sqrt(pow(_yoshida->getPositionX() - _touchStartPos.x, 2) + 
		pow(_yoshida->getPositionY() - _touchStartPos.y, 2));

	float yoshidaAngle = atan2(_yoshida->getPositionY() - _touchStartPos.y,
		_yoshida->getPositionX() - _touchStartPos.x)* 180.0f / M_PI;

	yoshidaAngle += yoshidaAngle > 0 ? 0 : 360;
	float angle = atan2(touchPos.y - _touchStartPos.y, touchPos.x - _touchStartPos.x)* 180.0f / M_PI;
	angle += angle > 0 ? 0 : 360;
	
	if (yosiRange <= 500 && 30 >= fabs(angle - yoshidaAngle)) {
		log("Hit");
		float windRange = sqrt(pow(touchPos.x - _yoshida->getPositionX(), 2) + pow(touchPos.y - _yoshida->getPositionY(), 2));

		if (windRange > 500)windRange = 500;
		float windCallCnt = windRange / 500;
		float delTime = yosiRange / 500;
		angle = angle / 180.0f * M_PI;
		Vec2 windEndPos = Vec2(cos(angle) * windRange, sin(angle) * windRange);
		auto mati = DelayTime::create(delTime);
		auto move = MoveBy::create(windCallCnt, windEndPos);
		auto eas = EaseOut::create(move, 3);
		auto func = CCCallFunc::create([=]()
		{
			Rect yoshiRect = _yoshida->getBoundingBox();
			for (int i = 0; i < _uekibati.size(); i++) 
			{
				Rect ueRect = _uekibati[i]->getBoundingBox();
				if (ueRect.intersectsRect(yoshiRect))
				{
					Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
				}
			}
		});
		auto maze = Sequence::create(mati, eas, func,nullptr);
		_yoshida->runAction(maze);

	}
	//    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));
}