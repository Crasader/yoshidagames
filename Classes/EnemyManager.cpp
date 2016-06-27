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
	
	// updateを毎フレーム実行するように登録する
	this->scheduleUpdate();

	return true;
}

void EnemyManager::update(float dt)
{
	posCheck();
	HitCheck();
}

void EnemyManager::posCheck() 
{
	for (auto enemy : _enemyArr) 
	{
		Vec2 enemyPos = enemy->getPosition();
		float minVec = 20000;
		Vec2 minYoshidaPos = Vec2(0, 0);

		for (auto yoshida : _yoshidaArr)
		{
			Vec2 yoshidaPos = yoshida->getPosition();
			float kyori = sqrt(pow(yoshidaPos.x - enemyPos.x, 2) + pow(yoshidaPos.y - enemyPos.y, 2));
			if (minVec > kyori)
			{
				minVec = kyori;
				minYoshidaPos = yoshidaPos;
			}
		}
		//敵の視覚範囲内に入ったら敵が動き出す
		float targetIn = 800;
		if (minYoshidaPos.x < enemyPos.x + targetIn && minYoshidaPos.x > enemyPos.x - targetIn)
		{
			enemy->_isMoved = true;
		}
		else 
		{
			enemy->_isMoved = false;
		}

		//近くに行くとホーミングをやめる
		float tikasugiDame = 200;
		if (minVec > tikasugiDame)
		{
			Vec2 yosidaTonoKyori = minYoshidaPos - enemy->getPosition();
			enemy->_yoshidatonoAngle = atan2(yosidaTonoKyori.y, yosidaTonoKyori.x);
		}
	}
}

void EnemyManager::HitCheck() 
{
	for (int target = 0; target < _enemyArr.size(); target++)
	{
		Rect enemyRect = _enemyArr.at(target)->getBoundingBox();

		for (auto item : _itemManager->_itemArr)
		{
			Rect itemRect = item->getBoundingBox();
			if (enemyRect.intersectsRect(itemRect))
			{

				auto rot = RotateTo::create(1.0, 180);
				auto fall = MoveTo::create(5.0, Vec2(_enemyArr.at(target)->getPosition().x, -100));
				auto spawn = Spawn::create(rot, fall, nullptr);

				auto func = CCCallFunc::create([=]()
				{
					_enemyArr.at(target)->removeFromParentAndCleanup(true);
					_enemyArr.erase(_enemyArr.begin() + target);
				});
				auto seq = Sequence::create(spawn,func,nullptr);
				_enemyArr.at(target)->runAction(seq);
			}
		}
	}
}