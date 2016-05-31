#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{

	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_backGround = Sprite::create("pix/buck/stage.png");
	_backGround->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(_backGround);

	Sprite *backGround2 = Sprite::create("pix/buck/stage.png");
	backGround2->setAnchorPoint(Vec2(0.0f, 0.0f));
	backGround2->setPosition(Vec2(_backGround->getBoundingBox().size.width, 0));
	addChild(backGround2);

	Sprite *ki = Sprite::create("pix/buck/ki.png");
	ki->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(ki);

	Sprite *uekibathi = Sprite::create("pix/stageSozai/uekibati.png");
	addChild(uekibathi,1);
	uekibathi->setAnchorPoint(Vec2(0.0f, 0.0f));
	uekibathi->setScale(0.7f);
	uekibathi->setPosition(Vec2(designResolutionSize.width*1.5f, designResolutionSize.height*0.24f));

	_kusahayasu = Kusahayasu::create();
	addChild(_kusahayasu);

	_stageCreater = new StageCreater();
	_stageCreater->init(uekibathi);
	_stageCreater->autorelease();
	addChild(_stageCreater);



	_effectManger = new EffectManager();
	_effectManger->init();
	_effectManger->autorelease();
	addChild(_effectManger);

	_yoshidaCamera = new YoshidaCamera();
	_yoshidaCamera->init();
	_yoshidaCamera->autorelease();
	addChild(_yoshidaCamera);

	_enemyManager = new EnemyManager();
	_enemyManager->init();
	_enemyManager->autorelease();
	addChild(_enemyManager);

	_yosidaManeger = new YoshidasanNoManager();
	_yosidaManeger->init(_stageCreater, _kusahayasu);
	_yosidaManeger->autorelease();
	_yosidaManeger->_effectManager = _effectManger;
	_yosidaManeger->_yoshidaCamera = _yoshidaCamera;
	_yosidaManeger->_enemyManager = _enemyManager;
	_enemyManager->
	addChild(_yosidaManeger);

	

	// タッチイベントを有効にする
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//playerの移動に画面がついていく
	this->runAction(Follow::create(_yoshidaCamera, Rect(0, 0, designResolutionSize.width * 2, designResolutionSize.height)));
	this->scheduleUpdate();


	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void HelloWorld::update(float dt)
{

}

//----------------------------------------------------------------------------------------------------------------
// タッチした瞬間に呼ばれるメソッド
//----------------------------------------------------------------------------------------------------------------
bool HelloWorld::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Vec2 touchPos = pTouch->getLocation();
	Vec2 yoshidaPos = _yoshidaCamera->getPosition();

	if (yoshidaPos.x >= designResolutionSize.width / 2)
	{
		touchPos.x += (yoshidaPos.x - designResolutionSize.width / 2);
	}
	if (yoshidaPos.x >= designResolutionSize.width*1.5)
	{
		touchPos.x -= yoshidaPos.x - designResolutionSize.width*1.5;
	}
	
	if((touchPos.x <= 50) && (touchPos.y <= 50))Director::getInstance()->replaceScene(HelloWorld::createScene());

	_yosidaManeger->touchCall(touchPos, true);
	_yosidaManeger->touchStateCall(touchPos);
	_yosidaManeger->yajirushiSet();

	_yoshidaCamera->_isMoved = true;

	_yosidaManeger->yajirushiSet();

	_yoshidaCamera->_isMoved = true;

	return true;
}

//----------------------------------------------------------------------------------------------------------------
// タッチされている時に呼ばれるメソッド
//----------------------------------------------------------------------------------------------------------------
void HelloWorld::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	Vec2 touchPos = pTouch->getLocation();
	Vec2 yoshidaPos = _yoshidaCamera->getPosition();

	if (yoshidaPos.x >= designResolutionSize.width / 2)
	{
		touchPos.x += (yoshidaPos.x - designResolutionSize.width / 2);
	}
	if (yoshidaPos.x >= designResolutionSize.width*1.5)
	{
		touchPos.x -= yoshidaPos.x - designResolutionSize.width*1.5;
	}

	_yosidaManeger->touchCall(touchPos, true);
	_yosidaManeger->yajirushiSet();
}

//----------------------------------------------------------------------------------------------------------------
// タッチが離された時によばれるメソッド
//----------------------------------------------------------------------------------------------------------------
void HelloWorld::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	Vec2 touchPos = pTouch->getLocation();
	Vec2 yoshidaPos = _yoshidaCamera->getPosition();

	if (yoshidaPos.x >= designResolutionSize.width / 2)
	{
		touchPos.x += (yoshidaPos.x - designResolutionSize.width / 2);
	}
	if (yoshidaPos.x >= designResolutionSize.width*1.5)
	{
		touchPos.x -= yoshidaPos.x - designResolutionSize.width*1.5;
	}
	_yosidaManeger->touchCall(touchPos, false);
	_yosidaManeger->touchEndCall(touchPos);
	//_touchSP->setRotation(_yosidaManeger->_kumomoAngle);

}

void HelloWorld::windEffect(Vec2 touchPos)
{
	int kirakiraDeru = 8;
	for (int i = 0; i < kirakiraDeru; i++)
	{
		_wind = Sprite::create();
		_wind->setTextureRect(Rect(0, 0, 32, 32));
		_wind->setColor(Color3B(255, 255, 100));
		int width = 3.0 - (i * 1.5);
		int height = 0 + (1.5 * i);
		_wind->setPosition(Vec2(touchPos.x + width, touchPos.y + height));
		_wind->setScale(0.3);
		addChild(_wind);

		Vec2 myVec = Vec2(width, height);
	    float myang = myVec.getAngle() * 180 / M_PI;
		_wind->setRotation(myang);

		auto act2 = MoveBy::create(1.5f, Vec2(width * 5, height * 5));	//動く
		auto act3 = FadeIn::create(1.5f);						//だんだん出
		auto act4 = ScaleBy::create(1.5f, 1.3);						//大きくなる
		auto spawn = Spawn::create(act2, act3, act4, nullptr);	// アクションを同時に実行
		auto act5 = RemoveSelf::create();						// 自分自身を削除
		auto sequence = Sequence::create(spawn, act5, nullptr); // アクションを順番に実行
		_wind->runAction(sequence);
	}
}