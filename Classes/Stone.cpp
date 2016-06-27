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
	setScale(0.8);

	_isWind = false;

	_speed = Vec2(0, 0);

	_rotCnt = 0;

	Vec2 StonePos = getPosition();

	this->scheduleUpdate();
	return true;
}

void Stone::update(float dt)
{
	//windSpeedDown();
	speedKeisan();
	//targetHitCheak();

	if (_isWind)
	{
		windHitMoveing();
	}
}

void Stone::windHitRotation()
{
	setRotation(getRotation() + _speed.x);
}

void Stone::windHitMoveing()
{
	windHitRotation();
	move();
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
	int p = 6;

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


}