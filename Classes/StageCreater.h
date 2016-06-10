//prototype create yoshidasan
//
//create by kagihiro
//
//StageCreater
//16/04/22


#ifndef  __StageCreater_H_
#define  __StageCreater_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "Windmill.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class StageCreater : public Node
{
public:
	bool init(Sprite *uekibati);
	void update(float dt);
	Rect getGoolRect();
	vector<Sprite*> getSyougaibutu();

	vector<Sprite*> _syougaibutu;
};
#endif
