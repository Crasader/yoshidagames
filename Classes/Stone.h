//prototype create yoshidasan
//
//create by shimada
//
//16/06/16


#ifndef  __Stone_H_
#define  __Stone_H_

#include "cocos2d.h"
#include "MultiResolution.h"

#include "Item.h"

using namespace cocos2d;
using namespace std;

class Stone : public Item
{
public:
	static Stone *create();
	bool init();
	void update(float dt);
	void windHitRotation();
	void windHitMoveing();
	void move();
	void speedKeisan();
	void targetHitCheak();

	float _rotCnt;
	vector<Sprite*> _syougaibutu;
};
#endif