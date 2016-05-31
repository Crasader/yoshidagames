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
#include "EffectManager.h"

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

	YoshidasanNoManager *_yoshiMana;
	EffectManager *_effectManager;

	Vec2 _touchStartPos;
	Vec2 _touchEndPos;
	Sprite *_yajirushiSP;
	bool _isTouch;

};
#endif
