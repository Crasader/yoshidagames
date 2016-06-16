//prototype create yoshidasan
//
//create by shimada
//
//16/06/13


#ifndef  __Item_H_
#define  __Item_H_

#include "cocos2d.h"
#include "MultiResolution.h"

using namespace cocos2d;

class Item : public Sprite
{
public:
	static Item *create();
	bool init();
	void update(float dt);
	void windHitMoveing();
	void windSet(bool isWind, Vec2 speed);
	void windStop();
	void windSpeedDown();

	bool _isWind;
	Vec2 _speed;
	float _rotCnt;
};
#endif