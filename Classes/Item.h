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
	void vecKeisan(Vec2 touchPos, float windRange, float actionTime);
	void setNoOverMaxSpeed();

	bool _isWind;
	bool _isGoRight;
	bool _isGoDown;

	int _maxSpeed;
	float _gSpeed;
	float _moveMaxX;
	float _windBoost;
	float _rotCnt;

	Vec2 _speed;
};
#endif