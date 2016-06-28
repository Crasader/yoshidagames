#include "Stone.h"

Stone * Stone::create()
{

	Stone *pRet = new Stone();
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

bool Stone::init()
{
	if (!Item::init())return false;
	initWithFile("pix/stageSozai/stone2.png");
	//setTextureRect(Rect(100, 100, 50, 50));
	setScale(0.6);

	_isWind = false;

	_speed = Vec2(0, 0);

	_maxSpeed = 30;

	_rotCnt = 0;
	_syougaibutu.clear();

	Vec2 StonePos = getPosition();

	this->scheduleUpdate();
	return true;
}

void Stone::update(float dt)
{
	//windSpeedDown();
	speedKeisan();
	//targetHitCheak();
	move();

	if (_isWind)
	{
		windHitMoveing();
	}
}

void Stone::windHitMoveing()
{
	windHitRotation();
}

void Stone::windHitRotation()
{
	setRotation(getRotation() + _speed.x);
}

void Stone::move()
{
	//ˆÚ“®—Ê‚ð‰ÁŽZ‚µ‚ÄƒCƒhƒE
	setPosition(Vec2(getPositionX() + _speed.x, getPositionY() + _speed.y));

	if (getPositionY() < designResolutionSize.height * 0.16f)
	{
		setPositionY(designResolutionSize.height * 0.16f);
	}
}

//speed‚ÌŒvŽZ
void Stone::speedKeisan()
{
	setNoOverMaxSpeed();

	//d—Í‚ðƒXƒs[ƒh‚ÌŒ¸­‚É‚Ç‚Ì’ö“x”½‰f‚·‚é‚©’²®
	int p = 5;

	//y•ûŒü‚Ì‰^“®—Ê‚ÌŒvŽZ-----------------------------------------------------
	if (!_isGoDown)	//ãŒü‚«
	{
		if (_speed.y > _gSpeed)
		{
			_speed.y += _gSpeed / p;
		}
		else
		{
			_speed.y = _gSpeed;
			_isGoDown = true;
		}
	}
	else            //‰ºŒü‚«
	{
		if (_speed.y < _gSpeed)
		{
			_speed.y -= _gSpeed / p;
		}

		else
		{
			_speed.y = _gSpeed;
		}
	}
	//------------------------------------------------------------------------

	//x•ûŒü‚Ì‰^“®—Ê‚ÌŒvŽZ-----------------------------------------------------
	if (_speed.x != 0)
	{
		if (_isGoRight)
		{
			if (_speed.x > _gSpeed)
			{
				_speed.x += _gSpeed / p;
			}
			else
			{
				_speed.x = 0;
			}
		}
		else
		{
			if (_speed.x < _gSpeed)
			{
				_speed.x -= _gSpeed / p;
			}
			else
			{
				_speed.x = 0;
			}
		}
	}
	//------------------------------------------------------------------------
}

void Stone::targetHitCheak()
{  
	Rect myRect = this->getBoundingBox();

	//áŠQ•¨‚Æ“–‚½‚Á‚Ä‚¢‚é‚©
	for (auto syougaibutu : _syougaibutu)
	{
		Rect syougaiRect = syougaibutu->getBoundingBox();
		Size syougaiSize = Size(syougaiRect.size.width, syougaiRect.size.height);
		syougaiRect = Rect{ syougaiRect.getMinX() + syougaiSize.width * 0.05f,
			syougaiRect.getMinY(),
			syougaiSize.width - syougaiSize.width * 0.1f,
			syougaiSize.height + 5 };

		if (myRect.intersectsRect(syougaiRect))
		{

			int angleNum = 0;
			float kyori = 100000;

			if (myRect.getMinY() <= syougaiRect.getMaxY() &&			//ã
				kyori >= syougaiRect.getMaxY() - myRect.getMinY())
			{
				_speed.y = _speed.y * -1;
				angleNum = 0;
				kyori = syougaiRect.getMaxY() - myRect.getMinY();
			}

			if (myRect.getMinX() <= syougaiRect.getMaxX() &&			//‰E
				kyori >= syougaiRect.getMaxX() - myRect.getMinX())
			{
				_speed.x = _speed.x * -1;
				angleNum = 1;
				kyori = syougaiRect.getMaxX() - myRect.getMinX();
			}

			if (myRect.getMaxY() >= syougaiRect.getMinY() &&			//‰º
				kyori >= myRect.getMaxY() - syougaiRect.getMinY())
			{
				_speed.y = _speed.y * -1;
				angleNum = 2;
				kyori = myRect.getMaxY() - syougaiRect.getMinY();
			}

			if (myRect.getMaxX() >= syougaiRect.getMinX() &&			//¶
				kyori >= myRect.getMaxX() - syougaiRect.getMinX())
			{
				_speed.x = _speed.x * -1;
				angleNum = 3;
				kyori = myRect.getMaxX() - syougaiRect.getMinX();
			}
			//isHit = true;
			break;
		}
	}
}