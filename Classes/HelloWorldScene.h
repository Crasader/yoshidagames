#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "YoshidasanNoManager.h"
#include "StageCreater.h"
#include "Kusahayasu.h"
#include "EffectManager.h"
#include "YoshidaCamera.h"
#include "EnemyManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float dt);

	YoshidasanNoManager *_yosidaManeger;
	// タッチイベント処理
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);


	Sprite *_backGround;
	StageCreater *_stageCreater;
	Kusahayasu *_kusahayasu;
	EffectManager *_effectManger;
	YoshidaCamera *_yoshidaCamera;
	EnemyManager *_enemyManager;

	Sprite *_wind;

	void windEffect(Vec2 touchPos);
};

#endif // __HELLOWORLD_SCENE_H__
