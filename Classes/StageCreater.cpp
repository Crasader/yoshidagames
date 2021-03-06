#include "StageCreater.h"



bool StageCreater::init(Sprite *uekibati)
{
	if (!Node::init())return false;

	Sprite *backGround = Sprite::create("pix/buck/stage.png");
	backGround->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(backGround);

	Sprite *backGround2 = Sprite::create("pix/buck/stage.png");
	backGround2->setAnchorPoint(Vec2(0.0f, 0.0f));
	backGround2->setPosition(Vec2(backGround->getBoundingBox().size.width, 0));
	addChild(backGround2);

	Sprite *ki = Sprite::create("pix/buck/ki.png");
	ki->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(ki);

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
	yajirushi2->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.65f));
	addChild(yajirushi2);

	auto rightAct = MoveBy::create(0.5, Vec2(20, 0));
	auto leftAct = MoveBy::create(0.5, Vec2(-20, 0));
	auto seq2 = Sequence::create(rightAct, leftAct, nullptr);
	auto rep2 = RepeatForever::create(seq2);
	yajirushi2->runAction(rep2);

	Sprite *iwa = Sprite::create("pix/stageSozai/stone.png");
	addChild(iwa);
	iwa->setAnchorPoint(Vec2(0.0f, 0.0f));
	iwa->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.12f));
	_syougaibutu.push_back(iwa);

	Sprite *iwa2 = Sprite::create("pix/stageSozai/stone.png");
	addChild(iwa2);
	iwa2->setAnchorPoint(Vec2(0.0f, 0.0f));
	iwa2->setPosition(Vec2(designResolutionSize.width*1.0f, designResolutionSize.height*0.12f));
	_syougaibutu.push_back(iwa2);

	Sprite *kirikabu = Sprite::create("pix/stageSozai/kirikabu.png");
	addChild(kirikabu);
	kirikabu->setAnchorPoint(Vec2(0.0f, 0.0f));
	kirikabu->setPosition(Vec2(designResolutionSize.width*1.46f, designResolutionSize.height*0.1f));
	_syougaibutu.push_back(kirikabu);

	Sprite *jimen = Sprite::create("pix/stageSozai/ground.png");
	jimen->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(jimen);

	Sprite *jimen2 = Sprite::create("pix/stageSozai/ground.png");
	jimen2->setAnchorPoint(Vec2(0.0f, 0.0f));
	jimen2->setPosition(Vec2(jimen->getBoundingBox().size.width, 0));
	addChild(jimen2);


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
		goolSize.height * 0.3f +10);


	return goolRect;
}

vector<Sprite*> StageCreater::getSyougaibutu()
{
	return _syougaibutu;
}
