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
#include "Stone.h"

#include "Item.h"
#include "ItemManager.h"

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
	vector<Item*> getItem();
	
	ItemManager *_itemManager;
	vector<Sprite*> _syougaibutu;
	vector<Item*> _itemArr;
};
#endif
