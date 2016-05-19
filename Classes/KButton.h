//
//__KButton__
//
//create by kagihiro
//
//2016/04/11
//
//画像とボタンを押したときの処理を書いたらボタンにするクラス
//使用例
//
//Sceneを作るクラスに行う
//-----------------------------------------------------------------
//KButton *kButton = KButton::getInstance();
//kButton->removeChild();
//addChild(kButton);
//kButton->buttonClear();
//------------------------------------------------------------------
//
//ボタンの追加したいクラスでおこなう
//------------------------------------------------------------------
//function<void(Sprite *sp)>func = [=](Sprite *sp)
//	{
//		やりたい処理(引数は必ずSprite *spにしないとエラーが起こる)
//	};
//↑spは当たったSpriteが返ってくる
//KButton *kButton = KButton::getInstance();
//kButton->setButton(画像, func);
//-------------------------------------------------------------------
//



#ifndef __KButton_CPP__H__
#define __KButton_CPP__H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class KButton :public Node
{
public:
	KButton();
	~KButton();
	virtual bool init();
	static KButton *_instance;
	static KButton *getInstance();
	void setButton(Sprite *sprite, function<void(Sprite *sp)> func);
	// タッチイベント処理
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void buttonClear();
	int getButtonNum();
	void removeChild();
private:
	//ボタン処理保存
	vector<function<void(Sprite *sp)>> _buttonFunc;
	//ボタンスプライト
	vector<Sprite*> _buttonSprite;
	//タッチしたスプライト
	Sprite *_isTouchSprite;
	//タッチしたスプライトの番号
	int _isTouchNum;
	
};
#endif