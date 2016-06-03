// prototype create yoshidasan
//
//create by kagihiro
//
//UekiCreater
//16/04/22


#ifndef  __UekiCreater_H_
#define  __UekiCreater_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class UekiCreater : public Node
{
public:
	bool init();
	void update(float dt);
	Rect getGoolRect();
	vector<Sprite*> getUeki();

	vector<Sprite*> _ueki;
};
#endif

