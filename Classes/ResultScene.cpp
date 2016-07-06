#pragma execution_character_set("utf-8") 

#include "ResultScene.h"
#include "SelectScene.h"
#include "TitleScene.h"

Scene *ResultScene::createScene(int yoshida, int girl, int yanki, int debu)
{
	auto scene = Scene::create();
	scene->addChild(ResultScene::create(yoshida, girl, yanki, debu));
	return scene;
}

ResultScene *ResultScene::create(int yoshida, int girl, int yanki, int debu)
{
	ResultScene *pRet = new ResultScene();
	if (pRet && pRet->init(yoshida, girl, yanki, debu))
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

bool ResultScene::init(int yoshida, int girl, int debu, int yanki)
{
	if (!FLayer::init()) return false;

	_changeScene = true;

	_mojiFontSize = 64;
	_suujiFontsize = 72;

	_mojiFontPas = "fonts/chihaya_kaku.ttf";
	_suujiFontPas = "fonts/rexlia_free.ttf";

	Sprite *back = Sprite::create("pix/Result/result.png");
	back->setAnchorPoint(Vec2::ZERO);
	back->setPosition(Vec2::ZERO);
	back->setTextureRect(Rect(0, 0, designResolutionSize.width + 30, designResolutionSize.height));
	back->setOpacity(150);
	addChild(back);

	vector<string> hyoujiMoji;
	hyoujiMoji.push_back("匹の吉田さんと");
	hyoujiMoji.push_back("匹の女の子と");
	hyoujiMoji.push_back("匹のデブと");
	hyoujiMoji.push_back("匹のヤンキーを");

	vector<int> hyouzisuuji;
	hyouzisuuji.push_back(yoshida);
	hyouzisuuji.push_back(girl);
	hyouzisuuji.push_back(debu);
	hyouzisuuji.push_back(yanki);


	mojitukuru(Vec2(designResolutionSize.width * 0.1, designResolutionSize.height * 0.8),	//ポジション
		"今回は",																			//文字
		_mojiFontPas,																		//フォントのパス
		80,																					//表示サイズ
		false);																				

	for (int i = 0; i < 4; i++)
	{
		auto kazu = StringUtils::toString(hyouzisuuji[i]);
		mojitukuru(Vec2(designResolutionSize.width * 0.3, designResolutionSize.height * (0.7f - (i * 0.1f) - 0.015)),
			kazu,
			_suujiFontPas,
			_suujiFontsize,
			true);

		mojitukuru(Vec2(designResolutionSize.width * 0.35, designResolutionSize.height * (0.7f - (i * 0.1f))),
			hyoujiMoji[i],
			_mojiFontPas,
			_mojiFontSize,
			false);
	}

	mojitukuru(Vec2(designResolutionSize.width * 0.6, designResolutionSize.height * 0.3),	//ポジション
		"育てました。",																		//文字
		_mojiFontPas,																		//フォントのパス
		_mojiFontSize,																		//表示サイズ
		false);

	auto taplabel = Label::createWithTTF("タップしてもどる", _mojiFontPas, _mojiFontSize);
	taplabel->setTextColor(Color4B::WHITE);
	taplabel->setAnchorPoint(Vec2(0.5, 0.5));
	taplabel->setPosition(Vec2(designResolutionSize.width * 0.5, designResolutionSize.height * 0.15));
	addChild(taplabel);

	taplabel->setOpacity(0);
	taplabel->runAction(Repeat::create(Sequence::create(FadeIn::create(1.0f),
		FadeOut::create(1.0f),
		NULL),
		-1));

	scheduleUpdate();
	return true;
}

void ResultScene::update(float delta)
{

}


bool ResultScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if (_changeScene)
	{
		_changeScene = false;

		Director::getInstance()->replaceScene(TransitionPageTurn::create(0.8, TitleScene::createScene(), false));
	}

	return true;
}

void ResultScene::mojitukuru(Vec2 hyoujiPos, string hyoujiMozi, const char * hyoujiFont, int hyoujiSize,bool isRight)
{
	auto label = Label::createWithTTF(hyoujiMozi, hyoujiFont, hyoujiSize);
	label->setTextColor(Color4B::WHITE);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(hyoujiPos);
	if(isRight)label->setHorizontalAlignment(TextHAlignment::RIGHT);	//テキストの水平位置を右寄せに
	addChild(label);


}
