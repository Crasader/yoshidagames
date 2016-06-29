#include "TitleScene.h"
#include "SelectScene.h"
#include "HelloWorldScene.h"

Scene *TitleScene::createScene()
{
	auto scene = Scene::create();
	scene->addChild(TitleScene::create());
	return scene;
}

TitleScene *TitleScene::create()
{
	TitleScene *pRet = new TitleScene();
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

bool TitleScene::init()
{
	if (!FLayer::init()) return false;

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("BGM.mp3");
	audio->playBackgroundMusic("BGM.mp3");

	Sprite *back = Sprite::create("pix/buck/stage.png");
	back->setAnchorPoint(Vec2::ZERO);
	back->setPosition(Vec2::ZERO);
	back->setTextureRect(Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
	//back->setColor(Color3B(92, 87, 97));
	addChild(back);

	//Yoshidasan *yoshida = Yoshidasan::create();
	//addChild(yoshida);

	kusahayasu();

	Sprite *ground = Sprite::create("pix/stageSozai/ground.png");
	ground->setAnchorPoint(Vec2::ZERO);
	ground->setPosition(Vec2::ZERO);
	addChild(ground);

	_yoshida = Sprite::create("pix/actor/yoshidasan.png");
	_yoshida->setScale(0.2);
	_yoshida->setPosition(Vec2(designResolutionSize.width * 0.8,
		designResolutionSize.height * 0.5));
	addChild(_yoshida, 100);

	_kumo = Sprite::create("pix/Title/kumomo.png");
	_kumo->setPosition(Vec2(designResolutionSize.width * 0.3,
		designResolutionSize.height * 0.5));
	addChild(_kumo, 100);
	auto huwa1 = ScaleTo::create(1.5, 0.8);
	auto huwa2 = ScaleTo::create(1.5, 1.0);
	auto huwahuwa = Sequence::create(huwa1, huwa2, nullptr);
	auto repeat = RepeatForever::create(huwahuwa);
	_kumo->runAction(repeat);

	//Sprite *wind = Sprite::create("pix/Title/wind.png");
	//wind->setPosition(Vec2(designResolutionSize.width * 0.6,
							  //designResolutionSize.height * 0.5));
	//addChild(wind, 100);


	float duration = 0.1;

	Sprite *titleLogo = Sprite::create("pix/Title/logo.png");
	titleLogo->setPosition(Vec2(designResolutionSize.width / 2,
		designResolutionSize.height * 0.8));
	addChild(titleLogo, 100);

	titleLogo->setPositionY(titleLogo->getPositionY() + designResolutionSize.height);
	titleLogo->runAction(EaseBounceOut::create(MoveBy::create(1.0, Vec2(0, -designResolutionSize.height))));

	Sprite *start = Sprite::create("pix/Title/swipetostart.png");
	start->setPosition(Vec2(designResolutionSize.width * 0.5,
		designResolutionSize.height * 0.2));
	start->setOpacity(0);
	start->runAction(Repeat::create(Sequence::create(FadeIn::create(1.0f),
		FadeOut::create(1.0f),
		NULL),
		-1));
	addChild(start, 102);

	_yubi = Sprite::create("pix/Title/yubi.png");
	addChild(_yubi, 101);
	_yubi->setPosition(Vec2(designResolutionSize.width * 0.3f, designResolutionSize.height * 0.35f));
	_yubi->setOpacity(200);

	auto move = MoveBy::create(2.0f, Vec2(designResolutionSize.width * 0.5f, 0));
	auto eou = EaseIn::create(move, 5);

	auto big = ScaleTo::create(0.2f, 1.2f);
	auto toumei = FadeTo::create(0.2f, 10);
	auto maze = Spawn::create(toumei, big, nullptr);

	auto hajime = MoveTo::create(0, Vec2(designResolutionSize.width * 0.3f, designResolutionSize.height * 0.35f));
	auto toumeimodo = FadeTo::create(0.2f, 200);
	auto tizi = ScaleTo::create(0, 1.0f);
	auto reset = Spawn::create(hajime, toumeimodo, tizi, nullptr);

	auto seq = Sequence::create(eou, maze, reset, nullptr);
	auto rep = RepeatForever::create(seq);
	_yubi->runAction(rep);

	_startX = 0;

	_isChangeScene = false;

	scheduleUpdate();
	return true;
}

void TitleScene::update(float delta)
{
	FLayer::update(delta);
}

void TitleScene::kusahayasu()
{
	_kusaSozai.clear();
	float kusaSumWidth = 0;
	int counter = 0;
	while (kusaSumWidth <= designResolutionSize.width)
	{
		Sprite *kusa = Sprite::create("pix/stageSozai/shitakusa.png");
		addChild(kusa);
		kusa->setScale(0.03f * random(1, 10));
		kusa->setAnchorPoint(Vec2(0.5f, 0.0f));
		kusa->setPosition(Vec2(kusaSumWidth, designResolutionSize.height * 0.14f));
		kusaSumWidth += kusa->getBoundingBox().size.width / 1.5f;
		_kusaSozai.pushBack(kusa);

		auto del = DelayTime::create(0.03f * counter);
		auto func = CCCallFunc::create([=]()
		{
			float kaukau = 5;
			float actionTime = 0.3f;
			auto hihi = SkewBy::create(actionTime * 2, -kaukau * 2, 0);
			auto mimi = SkewBy::create(actionTime * 2, kaukau * 2, 0);
			auto mama = Sequence::create(mimi, hihi, nullptr);
			auto rere = Repeat::create(mama, 40);

			auto setStart = SkewTo::create(1, kaukau, 0);
			auto eas = EaseOut::create(setStart, 1);
			auto rep = RepeatForever::create(mama);
			kusa->runAction(rep);
		});
		auto mix = Sequence::create(del, func, nullptr);
		kusa->runAction(mix);
		counter++;
	}


}

bool TitleScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	FLayer::onTouchBegan(touch, event);
	Vec2 touchPos = touch->getLocation();
	_startX = touchPos.x;

	return true;
}

void TitleScene::onTouchEnded(Touch * touch, Event * event)
{
	FLayer::onTouchEnded(touch, event);
	Vec2 touchPos = touch->getLocation();
	if(touchPos.x - _startX >= 100)touchAction();
}



void TitleScene::touchAction()
{
	_yubi->stopAllActions();
	_yubi->setOpacity(0);
	auto ikiwo = ScaleTo::create(0.5, 1.2);

	auto hakidasuCall = CallFunc::create([=]
	{
		auto wind = Sprite::create("pix/Title/wind.png");
		wind->setPosition(Vec2(designResolutionSize.width * 0.55,
			designResolutionSize.height * 0.5));
		wind->setScale(0.6, 0.6);
		addChild(wind);

		auto wind1 = FadeIn::create(0.8);
		auto wind2 = ScaleTo::create(0.8, 1.0);
		auto wind3 = MoveTo::create(1.2, Vec2(designResolutionSize.width * 1.1,
			designResolutionSize.height * 0.55));
		auto windAct = Spawn::create(wind1, wind2, wind3, nullptr);
		wind->runAction(windAct);


		auto hakidasu = ScaleTo::create(0.5, 0.6);

		auto yoshidamove = MoveTo::create(0.8, Vec2(designResolutionSize.width * 1.1,
			designResolutionSize.height * 0.6));
		auto yoshidakaiten = RotateTo::create(0.8, -40.0f);
		auto yoshidaAct = Spawn::create(yoshidamove, yoshidakaiten, nullptr);
		auto actionCall = CallFunc::create([=]
		{
			if (!_isChangeScene)
			{
				Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene(0)));
				Director::getInstance()->replaceScene(TransitionFade::create(1.0f, SelectScene::createScene()));
			}
		}
		);
		auto seq = Sequence::create(yoshidaAct, actionCall, nullptr);
		_yoshida->runAction(seq);

	});
	auto ikiwohakidasu = Sequence::create(ikiwo, hakidasuCall, nullptr);
	_kumo->runAction(ikiwohakidasu);
}