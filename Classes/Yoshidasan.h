//prototype create yoshidasan
//
//create by kagihiro
//
//16/04/22


#ifndef  _APP_Yoshidasan_H_
#define  _APP_Yoshidasan_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class Yoshidasan :public Sprite
{
public:
	virtual bool init(const char *fileName, int maxSpeed, float gravity, bool isYanki,int myNo);
	void update(float dt);
	//当たった時のspeed値イドウ
	void speedChange(Vec2 plusSpeed);
	//風からの移動量の計算
	void vecKeisan(Vec2 touchPos,float windRange, float actionTime);
	//speedの適用
	void speedKeisan();
	//rotateの計算
	void rotateKeisan();
	//speedを反転
	void speedFlip();
	//speedを調べる
	Vec2 getSpeed();
	//最大スピーどに抑える
	void setNoOverMaxSpeed();
	//動く
	void move();
	//ほかの吉田と会った時のアクション
	void hitAction(Vec2 movePos);

	//吉田アクションず
	//始めの飛び出し
	void startGo(Vec2 moveState, float dilayTime);
	//いつもの揺れ
	void actionYuraYura();
	//変化を戻す
	void allChangeReset();
	//ゴーールした時の動き
	void actionGoolMove(Vec2 centerPos, float dilay);
	void kazekaiten(float actontime);
	
	void happaPiyon(Vec2 muki);


	bool _isGoRight;
	bool _isGoDown;
	bool _isWind;
	bool _isYanki;
	bool _isGool;
	bool _isRool;
	bool _isHit;

	int _maxSpeed;
	int _myNo;
	float _gSpeed;
	float _moveMaxX;

	Vec2 _pSpeed;
	Rect _goolRect;
	
};

#endif

