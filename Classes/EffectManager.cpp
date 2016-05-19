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

void EffectManager::touchEffectCreate(Vec2 Pos) 
{
	int kirakiraDeru = 20;
	for (int i = 0; i<kirakiraDeru; i++)
	{
		_kirakira = Sprite::create("maru.png");
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