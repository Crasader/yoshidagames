//----------------------------------------------------------------------------------------------------------------
// テンプレートシーンクラス
// コピペ用
// TemplateScene.cpp
// CopyWright Ken.D.Ohishi 2015.11.07
//----------------------------------------------------------------------------------------------------------------
#include "TemplateScene.h"

using namespace cocos2d; // cocos2d内に定義されている同じクラス名（Layer　Scene等）を定義しないように注意

//----------------------------------------------------------------------------------------------------------------
// LayerをSceneに貼り付けて返すメソッド
//----------------------------------------------------------------------------------------------------------------
Scene* TemplateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TemplateScene::create();
	scene->addChild(layer);
	return scene;
}

//----------------------------------------------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------------------------------------------
TemplateScene::TemplateScene()
{
	// メンバ変数の初期化
	_frameCnt = 0;
	_isTouch = false;

}

//----------------------------------------------------------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------------------------------------------------------
TemplateScene::~TemplateScene()
{
	// メンバ変数の解放
}

//----------------------------------------------------------------------------------------------------------------
// 初期化処理：シーン（画面）の事前準備
//----------------------------------------------------------------------------------------------------------------
bool TemplateScene::init()
{
	if (!Layer::init())	return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// タッチイベントを有効にする
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TemplateScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TemplateScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TemplateScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// シーンが切り替わったことを、見た目で確認できるように、ラベルを用意
	auto label = Label::createWithTTF("TemplateScene", "fonts/Marker Felt.ttf", 24);
	label->setPosition(
		Vec2(
			origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height
		)
	);
	this->addChild(label, 1);

	// updateを毎フレーム実行するように登録する
	this->scheduleUpdate();

	// フレームカウンター初期化
	_frameCnt = 0;

	return true;
}

//----------------------------------------------------------------------------------------------------------------
// 毎フレーム呼ばれる処理
//----------------------------------------------------------------------------------------------------------------
void TemplateScene::update(float dt)
{
	_frameCnt++;	// フレームカウンターインクリメント

	CCLOG("cnt = %d", _frameCnt);
	CCLOG("isTouch = %d", _isTouch);

}
//----------------------------------------------------------------------------------------------------------------
// 画面遷移のトランジションが終了したた時に１度だけ呼ばれるメソッド
//----------------------------------------------------------------------------------------------------------------
void TemplateScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();


}

//----------------------------------------------------------------------------------------------------------------
// タッチした瞬間に呼ばれるメソッド
//----------------------------------------------------------------------------------------------------------------
bool TemplateScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	_isTouch = true;
	Vec2 touchPos = pTouch->getLocation();

	CCLOG("TouchPos = (%f, %f)", touchPos.x, touchPos.y);	// タッチ座標をデバッグ表示

	return true;
}

//----------------------------------------------------------------------------------------------------------------
// タッチされている時に呼ばれるメソッド
//----------------------------------------------------------------------------------------------------------------
void TemplateScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	
}

//----------------------------------------------------------------------------------------------------------------
// タッチが離された時によばれるメソッド
//----------------------------------------------------------------------------------------------------------------
void TemplateScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	_isTouch = false;
}
