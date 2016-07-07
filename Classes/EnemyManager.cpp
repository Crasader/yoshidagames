#include "EnemyManager.h"

bool EnemyManager::init(int stageNum)
{
	if (!Node::init())return false;

	

	switch (stageNum)
	{
	case 0:
		stage0();
		break;
	case 1:
		break;
	case 2:
		stage2();
		break;
	default:
		break;
	}

	
	_syougaibutuArr.clear();
	_syougaibutuArr = _syougaibutu->getSyougaibutu();
	// updateを毎フレーム実行するように登録する
	this->scheduleUpdate();

	return true;
}

void EnemyManager::update(float dt)
{
	posCheck();
	HitCheck();
	targetHitCheak();
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
		int targetIn = 600;
		if (targetIn > minVec)
		{
			enemy->_isMoved = true;
			//近くに行くまでホーミングをやる
			int tikasugiDame = 100;
			if (minVec > tikasugiDame)
			{
				//一フレームに曲げる角度 : (M_PI / 180) 一度
				float bendAngle = (M_PI / 180);
				//Vec2 yosidaTonoKyori = enemy->getPosition() - minYoshidaPos;
				Vec2 yosidaTonoKyori = minYoshidaPos - enemy->getPosition();
				float futarinoAngle = atan2(yosidaTonoKyori.y, yosidaTonoKyori.x);
				futarinoAngle += futarinoAngle > 0 ? 0 : M_PI * 2;
				futarinoAngle -= fmod(futarinoAngle, M_PI / 2) / 3.0f;
				enemy->_myAngle += enemy->_myAngle > futarinoAngle ? -bendAngle : bendAngle;
			}
		}
		else
		{
			enemy->_isMoved = false;
			//Vec2 yosidaTonoKyori = enemy->getPosition() - minYoshidaPos;
			Vec2 yosidaTonoKyori = minYoshidaPos - enemy->getPosition();
			float futarinoAngle = atan2(yosidaTonoKyori.y, yosidaTonoKyori.x);
			futarinoAngle += futarinoAngle > 0 ? 0 : M_PI * 2;
			enemy->_myAngle = futarinoAngle;
		}
	}

	for (auto iyaty :_iyanayatu)
	{
		Vec2 iyanayatuPos = iyaty->getPosition();
		float minVec = 20000;
		Vec2 minYoshidaPos = Vec2(0, 0);
		for (auto yoshida : _yoshidaArr)
		{
			Vec2 yoshidaPos = yoshida->getPosition();
			float kyori = sqrt(pow(yoshidaPos.x - iyanayatuPos.x, 2) + pow(yoshidaPos.y - iyanayatuPos.y, 2));
			if (minVec > kyori)
			{
				minVec = kyori;
				minYoshidaPos = yoshidaPos;
			}
		}
		if (minVec < 600)
		{
			float angle = atan2(iyaty->_head->getPositionY() - minYoshidaPos.y, minYoshidaPos.x - iyaty->_head->getPositionX()) * 180 / M_PI + 30;
			if (angle < -90)angle = -90;
			if (angle > 10)angle = 10;
			iyaty->headRotateSet(angle);
			if (minVec < 400)
			{
				iyaty->kazehukasu(_yoshidaArr);
			}
		}
		else
		{
			iyaty->headRotateSet(0);
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
				int kirasuu = 200;
				float actionTime = 0.5f;
				for (int i = 0; i < kirasuu; i++)
				{
					Sprite * kirakira = Sprite::create();
					int kiraSize = random(10, 30);
					kirakira->setTextureRect(Rect(0, 0, kiraSize, kiraSize));
					Vec2 kirarandmPos = Vec2(random(-20, 20), random(-20, 20));
					kirakira->setPosition(_enemyArr.at(target)->getPosition() + kirarandmPos);
					kirakira->setColor(Color3B::BLACK);
					addChild(kirakira);

					Vec2 kirakirandm = Vec2(random(-20, 20), random(-20, 20));
					auto move = MoveBy::create(actionTime, kirakirandm);
					auto eOutMove = EaseOut::create(move, 3);
					auto mini = ScaleTo::create(actionTime, 0.0f);
					auto kaiten = RotateBy::create(actionTime, 200);
					auto mazeru = Spawn::create(eOutMove, mini, kaiten, nullptr);
					auto desh = RemoveSelf::create();
					auto seq = Sequence::create(mazeru, desh, nullptr);
					kirakira->runAction(seq);


				}
				_enemyArr.at(target)->removeFromParentAndCleanup(true);
				_enemyArr.erase(_enemyArr.begin() + target);
			}
		}
	}
}

void EnemyManager::targetHitCheak()
{
	
	for (auto enemy : _enemyArr)
	{
		Rect myRect = enemy->getBoundingBox();
		//障害物と当たっているか
		for (auto syougaibutu : _syougaibutuArr)
		{
			Rect syougaiRect = syougaibutu->getBoundingBox();
			Size syougaiSize = Size(syougaiRect.size.width, syougaiRect.size.height);
			syougaiRect = Rect{ syougaiRect.getMinX() + syougaiSize.width * 0.05f,
				syougaiRect.getMinY(),
				syougaiSize.width - syougaiSize.width * 0.1f,
				syougaiSize.height + 5 };
			if (myRect.intersectsRect(syougaiRect))
			{
				
				int angleNum = 0;
				float kyori = 100000;

				if (myRect.getMinY() <= syougaiRect.getMaxY() &&			//上
					kyori >= syougaiRect.getMaxY() - myRect.getMinY())
				{
					angleNum = 1;
					kyori = syougaiRect.getMaxY() - myRect.getMinY();
				}

				if (myRect.getMinX() <= syougaiRect.getMaxX() &&			//右
					kyori >= syougaiRect.getMaxX() - myRect.getMinX())
				{
					angleNum = 2;
					kyori = syougaiRect.getMaxX() - myRect.getMinX();
				}

				if (myRect.getMaxY() >= syougaiRect.getMinY() &&			//下
					kyori >= myRect.getMaxY() - syougaiRect.getMinY())
				{
					angleNum = 3;
					kyori = myRect.getMaxY() - syougaiRect.getMinY();
				}

				if (myRect.getMaxX() >= syougaiRect.getMinX() &&			//左
					kyori >= myRect.getMaxX() - syougaiRect.getMinX())
				{
					angleNum = 4;
					kyori = myRect.getMaxX() - syougaiRect.getMinX();
				}

				switch (angleNum)
				{
				case 1://上
					enemy->setPosition(Vec2(enemy->getPosition().x,         enemy->getPosition().y + kyori));
					break;
				case 2://右
					enemy->setPosition(Vec2(enemy->getPosition().x + kyori, enemy->getPosition().y        ));
					break;
				case 3://下
					enemy->setPosition(Vec2(enemy->getPosition().x,         enemy->getPosition().y - kyori));
					break;
				case 4://左
					enemy->setPosition(Vec2(enemy->getPosition().x - kyori, enemy->getPosition().y        ));
					break;

				default:
					break;
				}
				//isHit = true;
				//break;
			}
		}
	}
}

void EnemyManager::stage0()
{
	/*IyanaYatsu *iyayatu = IyanaYatsu::create(Vec2(200, designResolutionSize.height*0.13f));
	addChild(iyayatu);
	_iyanayatu.pushBack(iyayatu);*/
}

void EnemyManager::stage2()
{
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
	enemy->setPosition(designResolutionSize.width * 0.8f, designResolutionSize.height * 0.9f);

	Enemy *enemy2 = new Enemy();
	enemy2->init(enemyPas, maxSpeed, gravity, yankiCheck, myNo);
	enemy2->autorelease();
	addChild(enemy2);
	_enemyArr.pushBack(enemy2);
	enemy2->setPosition(designResolutionSize.width * 3.8f, designResolutionSize.height * 0.9f);


}

