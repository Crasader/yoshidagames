//prototype create yoshidasan
//
//create by shimada
//
//16/06/08


#ifndef  __Windmill_H_
#define  __Windmill_H_

#include "cocos2d.h"
#include "MultiResolution.h"

#include "Item.h"

using namespace cocos2d;

class Windmill : public Item
{
public:
	static Windmill *create();
	bool init();
	void update(float dt);
	void windHitRotation();
	void windHitMoveing(float num);


	Vec2 _startPos;
	float _rotCnt;

	Node* _target;
};
#endif
