#ifndef __StreamTest__EffectManager__
#define __StreamTest__EffectManager__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class EffectManager : public Layer
{
public:
	static EffectManager *create();
	virtual bool init();

	void touchEffectCreate(Vec2 Pos);

	void watageBakusan(Vec2 bakusanPos);

	Sprite* _kirakira;

};
#endif