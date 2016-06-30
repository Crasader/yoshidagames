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

#include "Item.h"
#include "ItemManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class StageCreater : public Node
{
public:
	bool init(Sprite *uekibati,int stagenum);
	void update(float dt);
	Rect getGoolRect();
	vector<Sprite*> getSyougaibutu();
	vector<Item*> getItem();
	void createStagePart0();
	void createStagePart1();
	void createStagePart2();

	float _jimenHight;
	ItemManager *_itemManager;
	vector<Sprite*> _syougaibutu;
	vector<Item*> _itemArr;
};
#endif
