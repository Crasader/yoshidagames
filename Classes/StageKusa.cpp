#include "StageKusa.h"



StageKusa * StageKusa::create()
{

	StageKusa *pRet = new StageKusa();
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

bool StageKusa::init()
{
	if (!Node::init())return false;

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
		float actionTime = 2.0f;
		float kaukau = 10;

		auto del = DelayTime::create(0.03f * counter);

		auto hihi = SkewBy::create(actionTime *0.4f, -kaukau, 0);

		auto mimimi = SkewBy::create(actionTime * 0.4f, kaukau, 0);

		auto mama = Sequence::create(mimimi, hihi, nullptr);
		auto rere = Repeat::create(mama, 4);
		auto mimi = SkewBy::create(actionTime, kaukau * 2, 0);

		auto mamama = Sequence::create(del, mimi, rere, nullptr);
		kusa->runAction(mamama);
		counter++;
	}

	this->scheduleUpdate();
	return true;
}

void StageKusa::update(float dt)
{

}

void StageKusa::kazePatapata(Sprite *targetKusa, bool _isLeft, float delayTime, float caleCnt)
{
	targetKusa->stopAllActions();
	/*targetKusa->setScaleX(targetKusa->getScaleX()/ 1.25f);
	targetKusa->setScaleY(targetKusa->getScaleX()/ 0.75f);*/
	auto del = DelayTime::create(delayTime);
	auto skewStartAction = SkewTo::create(0.5f, 30 * (_isLeft * -2 + 1), 0);
	/*targetKusa->setScaleX(targetKusa->getScaleX()* 1.25f);
	targetKusa->setScaleY(targetKusa->getScaleX()* 0.75f);*/

	float actiontime = 0.2f;
	float kaukau = 5;
	int actionNum = (caleCnt - delayTime) / actiontime * 2 + 1;
	auto hihi = SkewBy::create(actiontime, kaukau * (_isLeft * -2 + 1), 0);

	auto mimimi = SkewBy::create(actiontime, -kaukau * (_isLeft * -2 + 1), 0);

	auto mama = Sequence::create(mimimi, hihi, nullptr);
	int repeatNum = (caleCnt - delayTime) / actiontime * 2 + 1;
	auto rere = Repeat::create(mama, repeatNum);

	auto seq = Sequence::create(del, skewStartAction, rere, nullptr);
	targetKusa->runAction(seq);

}

void StageKusa::kazeAtariKeisan(Vec2 touchStartPos, float windRange, float kumomoAngle, float caleCnt, int haniAngle)
{
	kumomoAngle = kumomoAngle > 0 ? kumomoAngle : kumomoAngle + 360;
	haniAngle += 10;
	for (auto kusa : _kusaSozai)
	{
		float kusaAngle = atan2(kusa->getPositionY() - touchStartPos.y, kusa->getPositionX() - touchStartPos.x) * 180.0f / M_PI;
		kusaAngle = kusaAngle > 0 ? kusaAngle : kusaAngle + 360;

		if (kusaAngle >= kumomoAngle - haniAngle && kusaAngle <= kumomoAngle + haniAngle)
		{
			float kusaRange = sqrt(pow(kusa->getPositionX() - touchStartPos.x, 2) + pow(kusa->getPositionY() - touchStartPos.y, 2));

			if (kusaRange < windRange)
			{
				kazePatapata(kusa, kusa->getPositionX() - touchStartPos.x > 0 ? false : true, kusaRange / windRange * caleCnt, caleCnt);
			}
		}
	}
}

