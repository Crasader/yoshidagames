//create by shimada
//
//16/05/27


#ifndef  __EnemyManager_H_
#define  __EnemyManager_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

#include "Enemy.h"
#include "Item.h"
#include "ItemManager.h"
#include "EffectManager.h"


using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class EnemyManager :public Node
{
public:
	bool init();
	void update(float dt);
	void posCheck();
	void HitCheck();

	Vector<Enemy*> _enemyArr;
	Vector<Yoshidasan*> _yoshidaArr;
	EffectManager *_effectManager;
	ItemManager *_itemManager;
	//vector<Item> *_itemArr;


};

#endif

