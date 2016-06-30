#include "HelloWorldScene.h"

USING_NS_CC;

Scene *HelloWorld::createScene(int StageNum)
{
	auto scene = Scene::create();
	scene->addChild(HelloWorld::create(StageNum));
	return scene;
}

HelloWorld *HelloWorld::create(int StageNum)
{
	HelloWorld *pRet = new HelloWorld();
	if (pRet && pRet->init(StageNum))
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



// on "init" you need to initialize your instance
bool HelloWorld::init(int StageNum)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_stageNum = StageNum;
	log("%d", _stageNum);
	_backGround = Sprite::create("pix/buck/stage.png");
	_backGround->setAnchorPoint(Vec2(0.0f, 0.0f));
	_backGround->setGlobalZOrder(-10.0f);
	addChild(_backGround);

	Sprite *backGround2 = Sprite::create("pix/buck/stage.png");
	backGround2->setAnchorPoint(Vec2(0.0f, 0.0f));
	backGround2->setPosition(Vec2(_backGround->getBoundingBox().size.width, 0));
	addChild(backGround2);

	Sprite *ki = Sprite::create("pix/buck/ki.png");
	ki->setAnchorPoint(Vec2(0.0f, 0.0f));
	ki->setGlobalZOrder(-5.0f);
	addChild(ki);

	_yoshidaCamera = new YoshidaCamera();
	_yoshidaCamera->init();
	_yoshidaCamera->autorelease();
	addChild(_yoshidaCamera);

	_stageKusa = new StageKusa();
	_stageKusa->_yoshiCame = _yoshidaCamera;
	_stageKusa->init();
	_stageKusa->autorelease();
	addChild(_stageKusa);
	 
	Sprite *uekibathi = Sprite::create("pix/stageSozai/uekibati.png");
	addChild(uekibathi,1);
	uekibathi->setAnchorPoint(Vec2(0.0f, 0.0f));
	uekibathi->setScale(0.7f);
	uekibathi->setPosition(Vec2(designResolutionSize.width*1.5f, designResolutionSize.height*0.24f));

	_kusahayasu = Kusahayasu::create();
	addChild(_kusahayasu);

	_stageCreater = new StageCreater();
	addChild(_stageCreater);

	_itemManager = new ItemManager();
	_itemManager->init();
	_itemManager->autorelease();
	addChild(_itemManager);

	_stageCreater->_itemManager = _itemManager;
	_stageCreater->init(uekibathi,_stageNum);
	_stageCreater->autorelease();


	_effectManger = new EffectManager();
	_effectManger->init();
	_effectManger->autorelease();
	addChild(_effectManger);

	

	_enemyManager = new EnemyManager();
	_enemyManager->init();
	_enemyManager->autorelease();
	_enemyManager->_itemManager = _itemManager;
	addChild(_enemyManager);

	_yosidaManeger = new YoshidasanNoManager();
	_yosidaManeger->_effectManager = _effectManger;
	_yosidaManeger->init(_stageCreater, _kusahayasu);
	_yosidaManeger->autorelease();
	_yosidaManeger->_yoshidaCamera = _yoshidaCamera;
	_yosidaManeger->_enemyManager = _enemyManager;
	addChild(_yosidaManeger);

	Sprite *kazehaniSP = Sprite::create("pix/eff/windpoint.png");
	addChild(kazehaniSP);

	_kumomo = new Kumomo();
	_kumomo->_yoshiMana = _yosidaManeger;
	_kumomo->_itemManager = _itemManager;
	_kumomo->_effectManager = _effectManger;
	_kumomo->_stageKusa = _stageKusa;
	_kumomo->_kazehaniSP = kazehaniSP;
	_kumomo->init();
	_kumomo->autorelease();
	addChild(_kumomo);
	

	// タッチイベントを有効にする
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//playerの移動に画面がついていく
	_scrollMAX = Vec2(designResolutionSize.width * 2, designResolutionSize.height);
	this->runAction(Follow::create(_yoshidaCamera, Rect(0, 0,_scrollMAX.x,_scrollMAX.y)));
	_yoshidaCamera->_scrollMAX = _scrollMAX;
	this->scheduleUpdate();


	return true;
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
	
	if((touchPos.x <= 50) && (touchPos.y <= 50))Director::getInstance()->replaceScene(HelloWorld::createScene(0));

	if (_yoshidaCamera->_isMoved == false) 
	{
		_yoshidaCamera->_isMoved = true;
	}

	_kumomo->touchStartCall(touchPos);
	
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

	_kumomo->touchCall(touchPos);
}

//----------------------------------------------------------------------------------------------------------------
//+ タッチが離された時によばれるメソッド
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

	_kumomo->touchEndCall(touchPos);

}


