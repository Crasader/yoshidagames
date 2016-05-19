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


	
	scheduleUpdate();
	return true;
}

void SelectScene::update(float delta)
{
	FLayer::update(delta);


}

bool SelectScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	FLayer::onTouchBegan(touch, event);

	return true;
}

void SelectScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	//    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));
}