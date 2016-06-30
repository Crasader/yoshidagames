#include "StageCreater.h"



bool StageCreater::init(Sprite *uekibati, int stagenum)
{
	if (!Node::init())return false;

	Sprite *yajirushi = Sprite::create("pix/stageSozai/yajirushi.png");
	yajirushi->setAnchorPoint(Vec2(0.0f, 0.0f));
	yajirushi->setScale(0.7f);
	yajirushi->setPosition(Vec2(designResolutionSize.width*1.48f, designResolutionSize.height*0.5f));
	addChild(yajirushi);

	auto upAct = MoveBy::create(0.5, Vec2(0, 20));
	auto downAct = MoveBy::create(0.5, Vec2(0, -20));
	auto seq = Sequence::create(upAct, downAct, nullptr);
	auto rep = RepeatForever::create(seq);
	yajirushi->runAction(rep);

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

	Sprite *kirikabu = Sprite::create("pix/stageSozai/kirikabu.png");
	addChild(kirikabu);
	kirikabu->setAnchorPoint(Vec2(0.0f, 0.0f));
	kirikabu->setPosition(Vec2(designResolutionSize.width*1.46f, designResolutionSize.height*0.1f));
	_syougaibutu.push_back(kirikabu);

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
	_syougaibutu.push_back(swipeBordBar);

	Sprite* swipeBord = Sprite::create("pix/stageSozai/swipeBoardB.png");
	swipeBord->setScale(1.0);
	swipeBord->setAnchorPoint(Vec2(0.0f, 0.0f));
	//windmillBord->setRotation(10);
	swipeBord->setPosition(Vec2(swipeBordBar->getPosition() + Vec2(-swipeBord->getBoundingBox().size.width*0.5 + swipeBordBar->getBoundingBox().size.width*0.5, swipeBordBar->getBoundingBox().size.height*0.6)));
	addChild(swipeBord);
	_syougaibutu.push_back(swipeBord);

	

	_itemManager->_syougaibutu = _syougaibutu;
	
	_itemManager->itemCreate(1, Vec2(designResolutionSize.width*0.3, designResolutionSize.height*0.18), NULL);

	//.push_back(windmill1);
	//------------------------------------------------------------------------------------------------------------------

}

void StageCreater::createStagePart1()
{

	Sprite* windmillBordBar = Sprite::create("pix/stageSozai/BoardBar.png");
	windmillBordBar->setScale(1.0);
	windmillBordBar->setAnchorPoint(Vec2(0.0f, 0.0f));
	//windmillBord->setRotation(10);
	windmillBordBar->setPosition(Vec2(designResolutionSize.width*1.3, _jimenHight - 20));
	addChild(windmillBordBar);
	_syougaibutu.push_back(windmillBordBar);

	Sprite* windmillBord = Sprite::create("pix/stageSozai/windmillBoardA.png");
	windmillBord->setScale(1.0);
	windmillBord->setAnchorPoint(Vec2(0.0f, 0.0f));
	//windmillBord->setRotation(10);
	windmillBord->setPosition(Vec2(windmillBordBar->getPosition() + Vec2(-windmillBord->getBoundingBox().size.width*0.5 + windmillBordBar->getBoundingBox().size.width*0.5, windmillBordBar->getBoundingBox().size.height*0.6)));
	addChild(windmillBord);
	_syougaibutu.push_back(windmillBord);

	//•—ŽÔ---------------------------------------------------------------------------------------------------------------
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
}

void StageCreater::createStagePart2()
{
}
