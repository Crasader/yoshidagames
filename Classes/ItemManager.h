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
	void touchEndCall(int haniAngle, float windRange, float angle, Vec2 touchStartPos, Vec2 windEndPos, float windTime);
	void kazeKeisan();
	void itemCreate(int ItemNo,Vec2 itemPos, Node *target);
	void windmillCreate(Vec2 itemPos, Node *target);
	void stoneCreate(Vec2 itemPos);

	vector<Item*> _itemArr;
	vector<Sprite*> _syougaibutu;
	vector<int> _taisyouItem;

	float _frmCount;
	float _windRange;
	float _speedtyousei;
	float _windCallCnt;
	float _windPowerBoost;
	float _kumomoAngle;
	float _windMaxTime;
	float _windMaxRange;
	Rect _goolRect;

	int _haniAngle;

	Vec2 _touchStartPos;
	Vec2 _yoshidaCenterPos;
};

#endif

