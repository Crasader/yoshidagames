#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

#include "YoshidasanNoManager.h"
#include "EnemyManager.h"

#include "StageCreater.h"
#include "Kusahayasu.h"
#include "EffectManager.h"
#include "YoshidaCamera.h"
#include "Kumomo.h"
#include "StageKusa.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class HelloWorld : public cocos2d::Layer
{
public:
    static Scene* createScene(int StageNum);
	static HelloWorld * create(int StageNum);

    virtual bool init(int StageNum);
    
    // implement the "static create()" method manually
    //CREATE_FUNC(HelloWorld(0));

	void update(float dt);

	YoshidasanNoManager *_yosidaManeger;
	// タッチイベント処理
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	StageCreater *_stageCreater;
	Kusahayasu *_kusahayasu;
	EffectManager *_effectManger;
	ItemManager *_itemManager;
	YoshidaCamera *_yoshidaCamera;
	EnemyManager *_enemyManager;
	Kumomo *_kumomo;
	StageKusa *_stageKusa;

	Vec2 _scrollMAX;
	int _stageNum;
};

#endif // __HELLOWORLD_SCENE_H__
