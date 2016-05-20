//
//  EffectManager.cpp
//  StreamTest
//
//  Created by Shimada on 2016/04/11.
//
//

#include "EffectManager.h"

EffectManager *EffectManager::create()
{
	EffectManager *pRet = new EffectManager();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool EffectManager::init()
{
	if (!Layer::init()) return false;


	return true;
}

//キラキラした玉が飛び散る
void EffectManager::touchEffectCreate(Vec2 Pos) 
{
	int kirakiraDeru = 20;
	for (int i = 0; i<kirakiraDeru; i++)
	{
		_kirakira = Sprite::create("pix/eff/maru.png");
		_kirakira->setTextureRect(Rect(0, 0, 32, 32));
		_kirakira->setColor(Color3B(255, 255, 100));
		//CCLOG("%f",Pos);
		_kirakira->setPosition(Pos);
		_kirakira->setScale(3);
		_kirakira->setColor(Color3B(155 + rand()%100,
			                        155 + rand()%100,
                                    155 + rand()%100));
		addChild(_kirakira);

		//srand((unsigned)time(NULL));
		//float ran = rand() % 100;

		// カラフルボールをランダムに配置する
		int width = -200 + (rand() % 400);//((int)designResolutionSize.width + 100));
		int height = -200 + (rand() % 400);//((int)designResolutionSize.height + 100));

		// カラフルボールをランダムな方向へ透過させながら移動させる
		auto act1 = RotateTo::create(1.0f, 270.0f);				// 270度回転した位置で止まる
		auto act2 = MoveBy::create(1.0f, Vec2(width, height));	//動く
		auto act3 = FadeOut::create(1.0f);						//だんだん消える
		auto act4 = ScaleBy::create(1.0f,0.2);						//小さくなる
		auto spawn = Spawn::create(act1, act2, act3,act4, nullptr);	// アクションを同時に実行
		auto act5 = RemoveSelf::create();						// 自分自身を削除
		auto sequence = Sequence::create(spawn, act5, nullptr); // アクションを順番に実行
		_kirakira->runAction(sequence);
	}
}

//わたげが爆散する(白い玉が飛び散る)
void EffectManager::watageBakusan(Vec2 bakusanPos) 
{
	int kirakiraDeru = 10;
	int hani = 50;
	for (int i = 0; i<kirakiraDeru; i++)
	{
		_kirakira = Sprite::create("pix/eff/maru.png");
		_kirakira->setTextureRect(Rect(0, 0, 32, 32));
		_kirakira->setColor(Color3B(255, 255, 255));
		//CCLOG("%f",Pos);
		_kirakira->setPosition(bakusanPos);
		//_kirakira->setScale(3);
		addChild(_kirakira);

		//srand((unsigned)time(NULL));
		//float ran = rand() % 100;

		// カラフルボールをランダムに配置する
		int width = -hani + (rand() % (hani* 2));//((int)designResolutionSize.width + 100));
		int height = -hani + (rand() % (hani * 2));//((int)designResolutionSize.height + 100));

										   // カラフルボールをランダムな方向へ透過させながら移動させる
		auto act1 = RotateTo::create(1.0f, 270.0f);				// 270度回転した位置で止まる
		auto act2 = MoveBy::create(1.0f, Vec2(width, height));	//動く
		auto act3 = FadeOut::create(1.0f);						//だんだん消える
		auto act4 = ScaleBy::create(1.0f, 0.2);						//小さくなる
		auto spawn = Spawn::create(act1, act2, act3, act4, nullptr);	// アクションを同時に実行
		auto act5 = RemoveSelf::create();						// 自分自身を削除
		auto sequence = Sequence::create(spawn, act5, nullptr); // アクションを順番に実行
		_kirakira->runAction(sequence);
	}
}

//波紋上に広がる
void EffectManager::hamonCreate(Vec2 Pos)
{
	_hamon = Sprite::create("pix/eff/maru.png");
	_hamon->setScale(2.0);
	_hamon->setPosition(Pos);
	addChild(_hamon);

	// フェードアウト
	auto act1 = FadeOut::create(0.5f);				//だんだん消えていく
	auto act2 = ScaleTo::create(0.5f, 3.0);			//大きくする
	auto spawn = Spawn::create(act1, act2, nullptr);	// アクションを同時に実行
	auto act4 = RemoveSelf::create();						// 自分自身を削除
	auto sequence = Sequence::create(spawn, act4, nullptr); // アクションを順番に実行
	_hamon->runAction(sequence);
}

//下に煙が噴射される
void EffectManager::hunsyaBusya(Vec2 Pos)
{
	for (int i = 0; i < 30; i++)
	{
		_smoke = Sprite::create("pix/eff/busya_e.png");
		_smoke->setPosition(Pos);
		int col = (rand() % 15);
		_smoke->setScale(0.8);
		_smoke->setColor(Color3B(240 + col, 240 + col, 255));
		addChild(_smoke);

		//ランダムに配置する
		float width = -200 + (rand() % 400); //*((rand() % 2 == 0) ? 1 : -1);
		float height = -800 + (rand() % 300);
		float speed = (rand() % 100 / 50) * 1 + 1.0;


		// ランダムな方向へ透過させながら移動させる
		// ジャンプのアクション
		auto act1 = JumpBy::create(
			speed,          // 期間
			Vec2(width, height - 30), // 着地座標
			height,        // 高さ
			1              // 回数
			);
		auto act2 = FadeOut::create(speed);						//だんだん消える
		auto spawn = Spawn::create(act1, act2, nullptr);	// アクションを同時に実行
		auto act3 = RemoveSelf::create();						// 自分自身を削除
		auto act4 = DelayTime::create((rand() % 80 / 100.0f));
		auto sequence = Sequence::create(act4, spawn, act3, nullptr); // アクションを順番に実行
		_smoke->runAction(sequence);
	}
}

//墨汁みたいな軌跡が出る
void EffectManager::createBokujyu(Vec2 Pos)
{
	int kirasuu = 30;
	float actionTime = 0.5f;
	for (int i = 0; i < kirasuu; i++)
	{
		Sprite * kirakira = Sprite::create();
		int kiraSize = random(10, 30);
		kirakira->setTextureRect(Rect(0, 0, kiraSize, kiraSize));
		Vec2 kirarandmPos = Vec2(random(-20, 20), random(-20, 20));
		kirakira->setPosition(Pos + kirarandmPos);
		//kirakira->setColor(Color3B(random(150,250), random(150, 250), random(150, 250)));
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
}