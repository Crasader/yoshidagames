//YoshidaGames Enemy
//
//create by shimada
//
//16/05/26


#ifndef  __Yoshida_Enemy__
#define  __Yoshida_Enemy__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

#include "Yoshidasan.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class Enemy :public Yoshidasan
{
public:
	bool init(const char *fileName, int maxSpeed, float gravity, bool isYanki, int myNo);
	void update(float dt);
	void enemyMove();

	float _speed;
	float _yoshidatonoAngle;
	Vec2 _yoshidaPos;
};

#endif