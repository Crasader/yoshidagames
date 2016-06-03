#include "UekiCreater.h"



bool UekiCreater::init()
{
	if (!Node::init())return false;

	Sprite *ueki1 = Sprite::create("pix/stageSozai/uekibati.png");
	addChild(ueki1);
	ueki1->setAnchorPoint(Vec2(0.0f, 0.0f));
	ueki1->setPosition(Vec2(designResolutionSize.width*1.46f, designResolutionSize.height*0.1f));
	_ueki.push_back(ueki1);


	this->scheduleUpdate();
	return true;
}

void UekiCreater::update(float dt)
{

}

Rect UekiCreater::getGoolRect()
{
	Rect goolRect = _ueki[_ueki.size() - 1]->getBoundingBox();
	Size goolSize = goolRect.size;
	goolRect = Rect(goolRect.getMinX(),
		goolRect.getMinY() + goolSize.height * 0.7f,
		goolSize.width,
		goolSize.height * 0.3f + 10);


	return goolRect;
}

vector<Sprite*> UekiCreater::getUeki()
{
	return _ueki;
}

