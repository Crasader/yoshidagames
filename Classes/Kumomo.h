//prototype create yoshidasan
//
//create by kagihiro
//
//16/05/27


#ifndef  __Kumomo_H_
#define  __Kumomo_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

#include "YoshidasanNoManager.h"
#include "ItemManager.h"
#include "EffectManager.h"
#include "StageKusa.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class Kumomo : public Sprite
{
public:
	static Kumomo *create();
	bool init();
	void update(float dt);
	void touchCall(Vec2 touchPos);
	void touchStartCall(Vec2 touchPos);
	void touchEndCall(Vec2 touchPos);
	void yajirushiSet();
	void kumomoActhionTigimu();
	void kumomoActionPuruPuru();
	void kumomoGiveWind();

	YoshidasanNoManager *_yoshiMana;
	EffectManager *_effectManager;
	ItemManager *_itemManager;
	StageKusa *_stageKusa;

	Vec2 _touchStartPos;
	Vec2 _touchEndPos;
	Sprite *_yajirushiSP;
	Sprite *_kazehaniSP;
	bool _isTouch;
	float _kumomoNomaX;
};
#endif
