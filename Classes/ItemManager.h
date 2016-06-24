//prototype create Itemsan
//
//create by shimada
//
//16/06/09


#ifndef  __ItemManager_H_
#define  __ItemManager_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

#include "StageCreater.h"
#include "Item.h"
#include "Windmill.h"
#include "Stone.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class ItemManager :public Node
{
public:
	bool init();
	void update(float dt);
	//static ItemManager *create();

	ItemManager* _itemManager;

	Vector<Item*> _item;
	vector<Sprite*> _syougaibutu;
	vector<int> _taisyouItem;

	bool _isTouch;

	Vec2 _touchStartPos;
	Vec2 _touchEndPos;
};

#endif

