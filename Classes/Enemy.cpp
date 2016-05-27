#include "Enemy.h"

bool Enemy::init(const char *fileName, int maxSpeed, float gravity, bool isYanki, int myNo)
{
	if (!Sprite::init())return false;
	initWithFile(fileName);
	setScale(0.2f);
	//重力の値
	_gSpeed = gravity;
	//プレイヤーの速度
	_pSpeed = Vec2(0, _gSpeed);
	//右向きに向かっているか
	_isGoRight = true;
	//下向きに向かっているか
	_isGoDown = true;
	//タッチしているか	
	_isWind = false;
	//ゴールしたかどうか
	_isGool = false;
	//やんきーかどうか
	_isYanki = isYanki;
	//自分の番号(ナニ田さんなのかの番号)
	_myNo = myNo;
	//最大移動速度
	_maxSpeed = maxSpeed;

	//ステージ内での最大移動量（X方向）
	_moveMaxX = (designResolutionSize.width * 2) - 100;

	// updateを毎フレーム実行するように登録する
	this->scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	if (!_isGool)speedKeisan();
	if (_isWind)rotateKeisan();
}
