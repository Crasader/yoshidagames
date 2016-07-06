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
		_kirakira = Sprite::create("pix/eff/maru.png");
		_kirakira->setTextureRect(Rect(0, 0, 32, 32));
		_kirakira->setColor(Color3B(255, 255, 100));
		//CCLOG("%f",Pos);
		_kirakira->setPosition(Pos);
		_kirakira->setScale(1);
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
		_kirakira = Sprite::create("pix/eff/watage.png");
		//_kirakira->setTextureRect(Rect(0, 0, 32, 32));
		_kirakira->setColor(Color3B(255, 255, 255));
		//CCLOG("%f",Pos);
		_kirakira->setPosition(bakusanPos);
		_kirakira->setScale(0.3);
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

void EffectManager::kumoDeru(Vec2 Pos) 
{
	int kumoDeru = 20;
	int hani = 10;
	for (int i = 0; i<kumoDeru; i++)
	{
		_sprite = Sprite::create("pix/eff/watage.png");
		//_kirakira->setTextureRect(Rect(0, 0, 32, 32));
		_sprite->setColor(Color3B(255, 255, 255));
		//CCLOG("%f",Pos);
		_sprite->setPosition(Pos);
		_sprite->setScale(0.3);
		//_sprite->setOpacity(0);
		addChild(_sprite);

		//srand((unsigned)time(NULL));
		//float ran = rand() % 100;

		// くもをランダムに配置する
		int width = -hani + (rand() % (hani * 2));//((int)designResolutionSize.width + 100));
		int height = -hani + (rand() % (hani * 2));//((int)designResolutionSize.height + 100));
		float randTime = (rand() % 10) * 0.5;
		_sprite->setPosition(Pos.x+width,Pos.y+height);

	    // くもを発生させて消す
		auto del = DelayTime::create(randTime);					//待つ
		auto act1 = ScaleTo::create(1.0f, 0.5f);				// 270度回転した位置で止まる
		auto act2 = FadeIn::create(1.0f);					//出てくる
		auto act3 = FadeOut::create(1.0f);						//だんだん消える
		//auto act4 = ScaleBy::create(1.0f, 0.2);					//小さくなる
		auto spawn = Spawn::create(act1,act2, nullptr);	// アクションを同時に実行
		auto act5 = RemoveSelf::create();						// 自分自身を削除
		auto sequence = Sequence::create(del,spawn,act3, act5, nullptr); // アクションを順番に実行
		_sprite->runAction(sequence);
	}
}

void EffectManager::kazeNagareru(Vec2 startPos, Vec2 endPos,float angle,float windCallTime) 
{
	int windDeru = 100;
	int angleHani = 20;
	int posHani = 100;
	for (int i = 0; i < windDeru; i++)
	{
		_wind = Sprite::create("pix/eff/windeff.png");
		_wind->setScale(0.2f);
		_wind->setPosition(Vec2(startPos));
		float windAngle = angle + (-angleHani + (rand() % (angleHani * 2)));
		_wind->setRotation(windAngle);
		Vec2 goPos = endPos + Vec2(float(-posHani + (rand() % (posHani * 2))), 0);//float(-posHani + (rand() % (posHani * 2))));
		addChild(_wind);

		auto delay = DelayTime::create((rand() % ((int)windCallTime+10) * 0.1));
		auto scale = ScaleTo::create(windCallTime,1.2);
		//auto moveAct = MoveTo::create(windCallTime, goPos);			//移動
		auto moveAct = JumpTo::create(
			windCallTime*1.5,
			goPos, // 着地座標
			0, // 高さ
			1              // 回数
			);
		auto ease = EaseBackOut::create(moveAct);
		auto fadeAct = FadeTo::create(windCallTime, 20);			//指定した透明度に変更
		auto removeAct = RemoveSelf::create();						//自分自身を削除
		auto spawn = Spawn::create(ease, fadeAct,scale, nullptr);
		auto sequence = Sequence::create(delay,spawn, removeAct, nullptr); // アクションを順番に実行
		_wind->runAction(sequence);
	}
}