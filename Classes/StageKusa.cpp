#include "StageKusa.h"

static float ACTIONTIME = 0.3f;

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

		auto del = DelayTime::create(0.03f * counter);
		auto func = CCCallFunc::create([=]()
		{
			itumonoPatapata(kusa , false);
		});
		auto mix = Sequence::create(del, func, nullptr);
		kusa->runAction(mix);
		counter++;
	}

	this->scheduleUpdate();
	return true;
}

void StageKusa::update(float dt)
{

}

void StageKusa::kazePatapata(Sprite *targetKusa, bool isLeft, float delayTime, float caleCnt)
{
	targetKusa->stopAllActions();
	/*targetKusa->setScaleX(targetKusa->getScaleX()/ 1.25f);
	targetKusa->setScaleY(targetKusa->getScaleX()/ 0.75f);*/
	auto del = DelayTime::create(delayTime);
	auto skewStartAction = SkewTo::create(0.3f, 30 * (isLeft * -2 + 1), 0);
	/*targetKusa->setScaleX(targetKusa->getScaleX()* 1.25f);
	targetKusa->setScaleY(targetKusa->getScaleX()* 0.75f);*/

	float kaukau = 5;
	int actionNum = (caleCnt - delayTime) / ACTIONTIME * 2 + 1;
	auto hihi	= SkewBy::create(ACTIONTIME, kaukau * (isLeft * -2 + 1), 0);

	auto mimimi = SkewBy::create(ACTIONTIME, -kaukau * (isLeft * -2 + 1), 0);

	auto mama	= Sequence::create(mimimi, hihi, nullptr);
	int repeatNum = (caleCnt - delayTime) / ACTIONTIME * 2 + 1;
	auto rere	= Repeat::create(mama, repeatNum);

	auto func = CCCallFunc::create([=]()
	{
		itumonoPatapata(targetKusa, isLeft);
	});
	auto seq	= Sequence::create(del, skewStartAction, rere, func, nullptr);
	targetKusa->runAction(seq);

}

void StageKusa::kazeAtariKeisan(Vec2 touchStartPos, float windRange, float kumomoAngle, float caleCnt, int haniAngle)
{
	haniAngle += 30;
	for (auto kusa : _kusaSozai)
	{
		Vec2 kusaPos = Vec2(kusa->getBoundingBox().getMidX(), kusa->getBoundingBox().getMaxY());
		float kusaAngle = atan2(kusaPos.y + - touchStartPos.y, kusaPos.x - touchStartPos.x) * 180.0f / M_PI;
		kusaAngle += kusaAngle > 0 ? 0 : 360;

		if (haniAngle  >= fabs( kumomoAngle - kusaAngle) &&
			(windRange >= fabs(kusaPos.y - touchStartPos.y) || windRange >= fabs(kusaPos.x - touchStartPos.x) ))
		{
			float kusaRange = sqrt(pow(kusaPos.x - touchStartPos.x, 2) + pow(kusaPos.y - touchStartPos.y, 2));

			if (kusaRange < windRange)
			{
				kazePatapata(kusa, kusaPos.x - touchStartPos.x > 0 ? false : true, kusaRange / windRange * caleCnt, caleCnt);
			}
		}
	}
}

void StageKusa::itumonoPatapata(Sprite * targetKusa, bool isLeft)
{
	targetKusa->stopAllActions();

	float kaukau = 5;

	auto hihi = SkewBy::create(ACTIONTIME * 2 , -kaukau * 2 * (isLeft * -2 + 1), 0);
	auto mimi = SkewBy::create(ACTIONTIME * 2 , kaukau * 2 * (isLeft * -2 + 1), 0);
	auto mama = Sequence::create(mimi, hihi, nullptr);
	auto rere = Repeat::create(mama, 40);

	auto setStart = SkewTo::create(1, kaukau * (isLeft * -2 + 1), 0);
	auto eas = EaseOut::create(setStart, 1);
	auto mamama = Sequence::create(eas, rere, nullptr);
	targetKusa->runAction(mamama);
}


