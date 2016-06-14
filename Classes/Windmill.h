//prototype create yoshidasan
//
//create by shimada
//
//16/06/08


#ifndef  __Windmill_H_
#define  __Windmill_H_

#include "cocos2d.h"
#include "MultiResolution.h"

using namespace cocos2d;

class Windmill : public Sprite
{
public:
	static Windmill *create();
	bool init();
	void update(float dt);
	void windHitRotation();
	void windHitMoveing();
	void windSet(bool isWind,Vec2 speed);
	void windStop();
	void windSpeedDown();

	bool _isWind;
	Vec2 _speed;
	float _rotCnt;

	Sprite* _target;
};
#endif
