#ifndef  _Yoshida_YoshidaCamera_H_
#define  _Yoshida_YoshidaCamera_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class YoshidaCamera :public Sprite
{
public:
	static YoshidaCamera *create();
	bool init();
	void update(float dt);
	void scrollMove();
	void moveOn();


	float _speed;
	bool _isMoved;
	bool _isScroll;
	Vec2 _yoshidaCenterPos;

};

#endif