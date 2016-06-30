#include "StageCreater.h"



bool StageCreater::init(Sprite *uekibati, int stagenum)
{
	if (!Node::init())return false;
	_uekibathi = uekibati;

	

	Sprite *yajirushi2 = Sprite::create("pix/stageSozai/yajirushi.png");
	yajirushi2->setAnchorPoint(Vec2(0.0f, 0.0f));
	yajirushi2->setScale(0.7f);
	yajirushi2->setRotation(-90);
	yajirushi2->setPosition(Vec2(designResolutionSize.width*0.3f, designResolutionSize.height*0.65f));
	addChild(yajirushi2);

	auto rightAct = MoveBy::create(0.5, Vec2(20, 0));
	auto leftAct = MoveBy::create(0.5, Vec2(-20, 0));
	auto seq2 = Sequence::create(rightAct, leftAct, nullptr);
	auto rep2 = RepeatForever::create(seq2);
	yajirushi2->runAction(rep2);

	

	Sprite *jimen = Sprite::create("pix/stageSozai/ground.png");
	jimen->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(jimen, 5);
	jimen->setTag(5);
	_syougaibutu.push_back(jimen);
	_jimenHight = jimen->getBoundingBox().size.height;

	Sprite *jimen2 = Sprite::create("pix/stageSozai/ground.png");
	jimen2->setAnchorPoint(Vec2(0.0f, 0.0f));
	jimen2->setPosition(Vec2(jimen->getBoundingBox().size.width, 0));
	addChild(jimen2, 5);
	jimen->setTag(5);
	_syougaibutu.push_back(jimen2);

	switch (stagenum)
	{
	case 0:
		createStagePart0();
		break;
	case 1:
		createStagePart1();
		break;
	case 2:
		createStagePart2();
		break;
	default:
		break;
	}

	
	_syougaibutu.push_back(uekibati);
	this->scheduleUpdate();
	return true;
}

void StageCreater::update(float dt)
{

}

Rect StageCreater::getGoolRect()
{
	Rect goolRect = _syougaibutu[_syougaibutu.size() - 1]->getBoundingBox();
	Size goolSize = goolRect.size;
	goolRect = Rect(goolRect.getMinX(),
		goolRect.getMinY() + goolSize.height * 0.7f,
		goolSize.width,
		goolSize.height * 0.3f + 10);


	return goolRect;
}

vector<Sprite*> StageCreater::getSyougaibutu()
{
	return _syougaibutu;
}

vector<Item*> StageCreater::getItem()
{
	return _itemArr;
}

void StageCreater::createStagePart0()
{

	

	Sprite* swipeBordBar = Sprite::create("pix/stageSozai/BoardBar.png");
	swipeBordBar->setScale(1.0);
	swipeBordBar->setAnchorPoint(Vec2(0.0f, 0.0f));
	//windmillBord->setRotation(10);
	swipeBordBar->setPosition(Vec2(designResolutionSize.width*0.2, _jimenHight - 20));
	addChild(swipeBordBar);
	//_syougaibutu.push_back(swipeBordBar);

	Sprite* swipeBord = Sprite::create("pix/stageSozai/swipeBoardB.png");
	swipeBord->setScale(1.0);
	swipeBord->setAnchorPoint(Vec2(0.0f, 0.0f));
	//windmillBord->setRotation(10);
	swipeBord->setPosition(Vec2(swipeBordBar->getPosition() + Vec2(-swipeBord->getBoundingBox().size.width*0.5 + swipeBordBar->getBoundingBox().size.width*0.5, swipeBordBar->getBoundingBox().size.height*0.6)));
	addChild(swipeBord);
	//_syougaibutu.push_back(swipeBord);

	_itemManager->_syougaibutu = _syougaibutu;
	
	Sprite *kirikabu = Sprite::create("pix/stageSozai/kirikabu.png");
	addChild(kirikabu);
	kirikabu->setAnchorPoint(Vec2(0.0f, 0.0f));
	kirikabu->setPosition(Vec2(designResolutionSize.width*1.46f, designResolutionSize.height*0.1f));
	_syougaibutu.push_back(kirikabu);

	_uekibathi->setPositionX(designResolutionSize.width * 1.5f);

	Sprite *yajirushi = Sprite::create("pix/stageSozai/yajirushi.png");
	yajirushi->setAnchorPoint(Vec2(0.0f, 0.0f));
	yajirushi->setScale(0.7f);
	yajirushi->setPosition(Vec2(designResolutionSize.width*1.46f, designResolutionSize.height*0.5f));
	addChild(yajirushi);

	auto upAct = MoveBy::create(0.5, Vec2(0, 20));
	auto downAct = MoveBy::create(0.5, Vec2(0, -20));
	auto seq = Sequence::create(upAct, downAct, nullptr);
	auto rep = RepeatForever::create(seq);
	yajirushi->runAction(rep);

}

void StageCreater::createStagePart1()
{
	//さぼ---------------------------------------------------------------------------------------------------------------

	Sprite *sabo1 = Sprite::create("pix/stageSozai/saboten3.png");
	sabo1->setAnchorPoint(Vec2(0.5f, 0.0f));
	sabo1->setPosition(Vec2(designResolutionSize.width * 0.8, _jimenHight-20));
	addChild(sabo1);
	_syougaibutu.push_back(sabo1);

	//さぼ---------------------------------------------------------------------------------------------------------------

	//banebu-------------------------------------------------------------------------------------------------------------

	Sprite *banebu = Sprite::create("pix/actor/banebu.png");
	banebu->setAnchorPoint(Vec2(0.5f, 0.0f));
	banebu->setPosition(Vec2(designResolutionSize.width * 2.2, _jimenHight - 20));
	addChild(banebu);
	_syougaibutu.push_back(banebu);
	banebu->setScale(0.7);
	float actionTime = 0.5f;
	auto act1 = ScaleBy::create(0.1, 1.2, 0.8);
	auto act2 = JumpBy::create(actionTime, Vec2(0, 0), 400.0, 1);
	auto act3 = ScaleBy::create(actionTime, 0.8, 1.3);
	auto act4 = ScaleBy::create(0.1, 1.3, 0.8);
	auto act5 = ScaleTo::create(0.1, 0.7, 0.7);
	auto didi = DelayTime::create(actionTime);
	auto spawn = Spawn::create(act2, act3, nullptr);	// アクションを同時に実行
	auto sequence = Sequence::create(act1, spawn, act4, act5,didi, nullptr); // アクションを順番に実行
	auto rere = RepeatForever::create(sequence);
	banebu->runAction(rere);
	//banebu-------------------------------------------------------------------------------------------------------------

	//風車---------------------------------------------------------------------------------------------------------------
	Sprite* windmillBordBar = Sprite::create("pix/stageSozai/BoardBar.png");
	windmillBordBar->setScale(1.0);
	windmillBordBar->setAnchorPoint(Vec2(0.0f, 0.0f));
	//windmillBord->setRotation(10);
	windmillBordBar->setPosition(Vec2(designResolutionSize.width*1.3, _jimenHight - 20));
	addChild(windmillBordBar);
	//_syougaibutu.push_back(windmillBordBar);

	Sprite* windmillBord = Sprite::create("pix/stageSozai/windmillBoardA.png");
	windmillBord->setScale(1.0);
	windmillBord->setAnchorPoint(Vec2(0.0f, 0.0f));
	//windmillBord->setRotation(10);
	windmillBord->setPosition(Vec2(windmillBordBar->getPosition() + Vec2(-windmillBord->getBoundingBox().size.width*0.5 + windmillBordBar->getBoundingBox().size.width*0.5, windmillBordBar->getBoundingBox().size.height*0.6)));
	addChild(windmillBord);
	//_syougaibutu.push_back(windmillBord);

	Sprite* gate = Sprite::create("pix/stageSozai/windmillD.png");
	gate->setAnchorPoint(Vec2(0.0f, 0.0f));
	gate->setPosition(Vec2(designResolutionSize.width*1.5, _jimenHight + 100));
	addChild(gate, -1);
	_syougaibutu.push_back(gate);

	Sprite* gate2 = Sprite::create("pix/stageSozai/windmillC.png");
	gate2->setAnchorPoint(Vec2(0.0f, 0.0f));
	gate2->setPosition(Vec2(gate->getPosition().x, _jimenHight - 10));
	addChild(gate2);
	_syougaibutu.push_back(gate2);

	Sprite* gate3 = Sprite::create("pix/stageSozai/windmillB.png");
	gate3->setAnchorPoint(Vec2(0.0f, 0.0f));
	gate3->setPosition(Vec2(gate->getPosition().x - gate->getBoundingBox().size.width / 2, gate->getPosition().y + gate->getBoundingBox().size.height - 20));
	addChild(gate3);
	_syougaibutu.push_back(gate3);

	_itemManager->itemCreate(0, gate->getPosition(), gate);

	Sprite *kirikabu = Sprite::create("pix/stageSozai/kirikabu.png");
	addChild(kirikabu);
	kirikabu->setAnchorPoint(Vec2(0.0f, 0.0f));
	kirikabu->setPosition(Vec2(designResolutionSize.width*2.76f, designResolutionSize.height*0.1f));
	_syougaibutu.push_back(kirikabu);

	_uekibathi->setPositionX(designResolutionSize.width * 2.8f);
}

void StageCreater::createStagePart2()
{
	_itemManager->itemCreate(1, Vec2(designResolutionSize.width*0.8f, _jimenHight), NULL);

	_itemManager->itemCreate(1, Vec2(designResolutionSize.width*2.5f, _jimenHight), NULL);
	Sprite *kirikabu = Sprite::create("pix/stageSozai/kirikabu.png");
	addChild(kirikabu);
	kirikabu->setAnchorPoint(Vec2(0.0f, 0.0f));
	kirikabu->setPosition(Vec2(designResolutionSize.width*3.76f, designResolutionSize.height*0.1f));
	_syougaibutu.push_back(kirikabu);

	_uekibathi->setPositionX(designResolutionSize.width * 3.8f);


	//banebu-------------------------------------------------------------------------------------------------------------

	Sprite *banebu = Sprite::create("pix/actor/banebu.png");
	banebu->setAnchorPoint(Vec2(0.5f, 0.0f));
	banebu->setPosition(Vec2(designResolutionSize.width * 1.5, _jimenHight - 20));
	addChild(banebu);
	_syougaibutu.push_back(banebu);
	banebu->setScale(0.7);
	float actionTime = 0.5f;
	auto act1 = ScaleBy::create(0.1, 1.2, 0.8);
	auto act2 = JumpBy::create(actionTime, Vec2(0, 0), 400.0, 1);
	auto act3 = ScaleBy::create(actionTime, 0.8, 1.3);
	auto act4 = ScaleBy::create(0.1, 1.3, 0.8);
	auto act5 = ScaleTo::create(0.1, 0.7, 0.7);
	auto didi = DelayTime::create(actionTime);
	auto spawn = Spawn::create(act2, act3, nullptr);	// アクションを同時に実行
	auto sequence = Sequence::create(act1, spawn, act4, act5, didi, nullptr); // アクションを順番に実行
	auto rere = RepeatForever::create(sequence);
	banebu->runAction(rere);
	//banebu-------------------------------------------------------------------------------------------------------------

	//renga--------------------------------------------------------------------------------------------------------------
	Sprite *rengaMini = Sprite::create("pix/stageSozai/renga2.png");
	rengaMini->setAnchorPoint(Vec2(0.5f, 0.0f));
	rengaMini->setPosition(Vec2(designResolutionSize.width * 2.0, _jimenHight - 20));
	addChild(rengaMini);
	_syougaibutu.push_back(rengaMini);

	Sprite *rengaBig = Sprite::create("pix/stageSozai/renga1.png");
	rengaBig->setAnchorPoint(Vec2(0.5f, 0.0f));
	rengaBig->setPosition(Vec2(designResolutionSize.width * 2.14, _jimenHight - 20));
	addChild(rengaBig);
	_syougaibutu.push_back(rengaBig);
	//renga--------------------------------------------------------------------------------------------------------------

	Sprite* gate = Sprite::create("pix/stageSozai/windmillD.png");
	gate->setAnchorPoint(Vec2(0.0f, 0.0f));
	gate->setPosition(Vec2(designResolutionSize.width*2.9, _jimenHight + 100));
	addChild(gate, -1);
	_syougaibutu.push_back(gate);

	Sprite* gate2 = Sprite::create("pix/stageSozai/windmillC.png");
	gate2->setAnchorPoint(Vec2(0.0f, 0.0f));
	gate2->setPosition(Vec2(gate->getPosition().x, _jimenHight - 10));
	addChild(gate2);
	_syougaibutu.push_back(gate2);

	Sprite* gate3 = Sprite::create("pix/stageSozai/windmillB.png");
	gate3->setAnchorPoint(Vec2(0.0f, 0.0f));
	gate3->setPosition(Vec2(gate->getPosition().x - gate->getBoundingBox().size.width / 2, gate->getPosition().y + gate->getBoundingBox().size.height - 20));
	addChild(gate3);
	_syougaibutu.push_back(gate3);

	_itemManager->itemCreate(0, gate->getPosition(), gate);
}
