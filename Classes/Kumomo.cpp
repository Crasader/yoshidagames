#include "Kumomo.h"

static const int KAZEHANIANGLE = 30;
static const float WINDMAXRANGE = 500.0f;//風の最大範囲
static const float WINDCALLMAXTIME = 1.0f;//風が流れ切るまでの最大時間


Kumomo * Kumomo::create()
{

		Kumomo *pRet = new Kumomo();
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

bool Kumomo::init()
{
	if (!Sprite::init()) return false;

	initWithFile("pix/Title/kumomo.png");
	setScale(0.2f);
	
	_touchStartPos = Vec2::ZERO;
	_touchEndPos = Vec2::ZERO;

	_isTouch = false;

	_yajirushiSP = Sprite::create("pix/eff/yajirushiYoko.png");
	_yajirushiSP->setPosition(500, 150);
	_yajirushiSP->setScale(0.8);
	addChild(_yajirushiSP);

	
	_kazehaniSP->setAnchorPoint(Vec2(0.0f, 0.5f));
	_kazehaniSP->setPositionX(getBoundingBox().size.height/2);
	_kumomoNomaX = 1.0f / _kazehaniSP->getBoundingBox().size.width;
	_kazehaniSP->setScale(_kumomoNomaX);

	_yoshiMana->_windMaxTime = WINDCALLMAXTIME;
	_yoshiMana->_windMaxRange = WINDMAXRANGE;
	_itemManager->_windMaxTime = WINDCALLMAXTIME;
	_itemManager->_windMaxRange = WINDMAXRANGE;

	this->scheduleUpdate();
	return false;
}

void Kumomo::update(float dt)
{
}

void Kumomo::touchCall(Vec2 touchPos)
{
	_touchEndPos = touchPos;
	yajirushiSet();
}


void Kumomo::touchStartCall(Vec2 touchPos)
{
	_isTouch = true;
	setPosition(touchPos);
	_touchStartPos = touchPos;
	_kazehaniSP->setPosition(touchPos);
	_kazehaniSP->setVisible(true);
	yajirushiSet();

}

void Kumomo::touchEndCall(Vec2 touchPos)
{
	_touchEndPos = touchPos;
	_isTouch = false;
	kumomoActhionTigimu();
	_kazehaniSP->setVisible(false);
}

void Kumomo::yajirushiSet()
{
	float maxRange = _yoshiMana->getMaxRange();
	//タッチしはじめと終わりのベクトルから角度を算出（右から上でひだりまでに0~+180,右から下で左までに0~-180）
	float angle = atan2(_touchStartPos.y - _touchEndPos.y, _touchEndPos.x - _touchStartPos.x) * 180.0f / M_PI ;
	float hani = sqrt(pow(_touchEndPos.x - _touchStartPos.x, 2) + pow(_touchEndPos.y - _touchStartPos.y, 2));
	if (hani > maxRange)hani = maxRange;
	float MaxKumomoBai = 2.0f;
	setScale(0.2f * MaxKumomoBai * hani / maxRange + 0.2f);
	_kazehaniSP->setScale(hani * _kumomoNomaX);
	setRotation(angle);
	int atherColor = (int)(135 * ((maxRange - hani) / maxRange)) + 120;
	setColor(Color3B(230, atherColor, atherColor));

	_kazehaniSP->setRotation(angle);
}

void Kumomo::kumomoActhionTigimu()
{
	auto hukuramu = ScaleBy::create(0.1f, 1.0f);
	auto func = CCCallFunc::create([=]() 
	{
		kumomoGiveWind();
	});
	float tizimiTIme = 0.2f;
	auto tizi = ScaleTo::create(tizimiTIme, 0.2f);
	auto easIn = EaseIn::create(tizi, 3);
	auto colorBack = TintTo::create(tizimiTIme, Color3B(255, 255, 255));
	auto spw = Spawn::create(func, easIn, colorBack, nullptr);
	auto seq = Sequence::create(hukuramu, spw, nullptr);
	runAction(seq);	
}

void Kumomo::kumomoActionPuruPuru() 
{
	auto puru1 = MoveBy::create(0.1f, Vec2(5,0));
	auto puru2 = MoveBy::create(0.1f, Vec2(-5, 0));
	auto seq = Sequence::create(puru1, puru2, nullptr);
	runAction(seq);
}

void Kumomo::kumomoGiveWind() 
{
	float windRange = sqrt(pow(_touchEndPos.x - _touchStartPos.x, 2) + pow(_touchEndPos.y - _touchStartPos.y, 2));
	if (windRange > WINDMAXRANGE)windRange = WINDMAXRANGE;
	float windCallCnt = WINDCALLMAXTIME * (windRange / WINDMAXRANGE);
	float angle = atan2(_touchEndPos.y - _touchStartPos.y, _touchEndPos.x - _touchStartPos.x);
	Vec2 windEndPos = Vec2(cos(angle) * windRange, sin(angle) * windRange) + _touchStartPos;
	angle = angle * 180.0f / M_PI;
	angle += angle > 0 ? 0 : 360;
	_yoshiMana->touchEndCall(KAZEHANIANGLE, windRange, angle, _touchStartPos, windEndPos, windCallCnt);
	_itemManager->touchEndCall(KAZEHANIANGLE, windRange, angle, _touchStartPos, windEndPos, windCallCnt);
	_stageKusa->kazeAtariKeisan(_touchStartPos,windRange, angle, windCallCnt, KAZEHANIANGLE);

}
