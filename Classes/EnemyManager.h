//create by shimada
//
//16/05/27


#ifndef  __EnemyManager_H_
#define  __EnemyManager_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

#include "Enemy.h"
#include "EffectManager.h"


using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class EnemyManager :public Node
{
public:
	bool init();
	void update(float dt);

	Vector<Enemy*> _enemyArr;

	EffectManager *_effectManager;

};

#endif

