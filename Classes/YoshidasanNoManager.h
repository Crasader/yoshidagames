//prototype create yoshidasan
//
//create by kagihiro
//
//16/04/22

#ifndef  __YoshidasanNoManager_H_
#define  __YoshidasanNoManager_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

#include "Yoshidasan.h"
#include "StageCreater.h"
#include "Kusahayasu.h"
#include "ResultScene.h"
#include "EffectManager.h"
#include "YoshidaCamera.h"

#include "EnemyManager.h"
#include "ItemManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class YoshidasanNoManager :public Node
{
public:
	bool init(StageCreater *stageCrater, Kusahayasu *kusahayasu);
	void update(float dt);
	//static YoshidasanNoManager *create();
	void touchEndCall(int haniAngle, float windRange, float angle, Vec2 touchStartPos, Vec2 windEndPos, float windTime);
	void yosidaLiveingCheck();
	void yoshidaNoAtarihantei();
	void kazeKeisan();
	void yoshidaCenterCall();
	void yoshidaWatashi();
	void yoshidaBorn(Vec2 targetPos);

	float getMaxRange();


	Vector<Yoshidasan*> _yoshida;
	vector<Sprite*> _syougaibutu;
	//vector<Item*> _itemArr;
	vector<int> _taisyouYoshida;
	//vector<int> _taisyouItem;

	StageCreater *_stageCrater;
	Kusahayasu *_kusahayasu;
	EffectManager *_effectManager;
	YoshidaCamera* _yoshidaCamera;
	EnemyManager* _enemyManager;

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

