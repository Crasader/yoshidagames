#include "EnemyManager.h"

bool EnemyManager::init()
{
	if (!Node::init())return false;

	const char *enemyPas = "pix/actor/enemyteki.png";
	float gravity = -0.98f;
	int maxSpeed = 10;
	bool yankiCheck = false;
	int myNo = 0;

	Enemy *enemy = new Enemy();
	enemy->init(enemyPas, maxSpeed, gravity, yankiCheck, myNo);
	enemy->autorelease();
	_enemyArr.pushBack(enemy);
	addChild(_enemyArr.at(0));
	_enemyArr.at(0)->setPosition(designResolutionSize.width, designResolutionSize.height * 0.9f);
	
	// update�𖈃t���[�����s����悤�ɓo�^����
	this->scheduleUpdate();

	return true;
}

void EnemyManager::update(float dt)
{

}