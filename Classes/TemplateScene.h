//----------------------------------------------------------------------------------------------------------------
// テンプレートシーンクラス
// コピペ用
// templateScene.h
// CopyWright Ken.D.Ohishi 2015.11.07
//----------------------------------------------------------------------------------------------------------------
#ifndef __TEMPLATE_SCENE_H__
#define __TEMPLATE_SCENE_H__

#include "cocos2d.h"

//----------------------------------------------------------------------------------------------------------------
// TemplateSceneクラスの定義：シーンクラスはLayerクラスを継承する
//----------------------------------------------------------------------------------------------------------------
class TemplateScene : public cocos2d::Layer
{
protected:
	TemplateScene();							// コンストラクタ
	virtual ~TemplateScene();					// デストラクタ

	virtual bool init();						// 初期化
	virtual void update(float dt);				// 更新
	virtual void onEnterTransitionDidFinish();	// 

	// タッチイベント処理
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

public:											
	static cocos2d::Scene* createScene();		// 

	CC_SYNTHESIZE(bool, _isTouch, IsTouch);				// タッチ判定フラグ
	CC_SYNTHESIZE(unsigned int, _frameCnt, FrameCnt);	// フレームカウンター

	// createメソッドを自動的に作成する仕組み（コンビニエンスコンストラクタ）
	CREATE_FUNC(TemplateScene);

};

#endif // __TEMPLATE_SCENE_H__
