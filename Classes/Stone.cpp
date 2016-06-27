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
	//�ړ��ʂ����Z���ăC�h�E
	setPosition(Vec2(getPositionX() + _speed.x, getPositionY() + _speed.y));

	if (getPositionY() < designResolutionSize.height * 0.16f)
	{
		setPositionY(designResolutionSize.height * 0.16f);
	}
}

//speed�̌v�Z
void Stone::speedKeisan()
{
	setNoOverMaxSpeed();

	//�d�͂��X�s�[�h�̌����ɂǂ̒��x���f���邩����
	int p = 6;

	//y�����̉^���ʂ̌v�Z-----------------------------------------------------
	if (!_isGoDown)	//�����
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
	else            //������
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

	//x�����̉^���ʂ̌v�Z-----------------------------------------------------
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