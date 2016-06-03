#include "EnemyManager.h"

bool EnemyManager::init()
{
	if (!Node::init())return false;

	const char *enemyPas = "pix/actor/yoshidateki.png";
	float gravity = 0.0f;
	int maxSpeed = 10;
	bool yankiCheck = false;
	int myNo = 0;

	Enemy *enemy = new Enemy();
	enemy->init(enemyPas, maxSpeed, gravity, yankiCheck, myNo);
	enemy->autorelease();
	addChild(enemy);
	_enemyArr.pushBack(enemy);
	enemy->setPosition(designResolutionSize.width, designResolutionSize.height * 0.9f);
	
	// update‚ð–ˆƒtƒŒ[ƒ€ŽÀs‚·‚é‚æ‚¤‚É“o˜^‚·‚é
	this->scheduleUpdate();

	return true;
}

void EnemyManager::update(float dt)
{
	posCheck();
}

void EnemyManager::posCheck() 
{
	for (auto enemy : _enemyArr) 
	{
		Vec2 enemyPos = enemy->getPosition();
		float minVec = 20000;
		Vec2 minYoshidaPos = Vec2(0, 0);

		for (auto yoshida:_yoshidaArr)
		{
			Vec2 yoshidaPos = yoshida->getPosition();
			float kyori = sqrt(pow(yoshidaPos.x - enemyPos.x, 2) + pow(yoshidaPos.y - enemyPos.y, 2));
			if (minVec > kyori) 
			{
				minVec = kyori;
				minYoshidaPos = yoshidaPos;
			}
		}
		float tikasugiDame = 100;
		if (minVec > tikasugiDame)
		{
			enemy->_yoshidaPos = minYoshidaPos;
		}
	}
}