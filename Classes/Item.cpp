#include "Item.h"

Item *Item::create()
{

	Item *pRet = new Item();
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

bool Item::init()
{
	//���x
	_speed = Vec2(0, 0);
	//�d�͂̒l
	_gSpeed = -1.6;
	//�E�����Ɍ������Ă��邩
	_isGoRight = true;
	//�������Ɍ������Ă��邩
	_isGoDown = true;
	//���ɓ������Ă��邩�ǂ���
	_isWind = false;
	//�ő�ړ����x
	_maxSpeed = 20;

	_windBoost = 1.0f;

	//�X�e�[�W���ł̍ő�ړ��ʁiX�����j
	_moveMaxX = (designResolutionSize.width * 2) - 100;

	_rotCnt = 0;

	Vec2 ItemPos = getPosition();

	this->scheduleUpdate();
	return false;
}

void Item::update(float dt)
{
	windSpeedDown();

	if (_isWind)
	{
		windHitMoveing();
	}
}

void Item::windHitMoveing()
{

}

void Item::windSet(bool isWind, Vec2 speed)
{
	_isWind = isWind;
	_speed = speed;
}

void Item::windStop()
{
	_isWind = false;
	_speed = Vec2(0, 0);
}

void Item::windSpeedDown()
{
	if (_speed.x > 0) _speed.x -= 0.05;
	if (_speed.x < 0) _speed.x += 0.05;
	if (_speed.y > 0) _speed.y -= 0.05;
	if (_speed.y < 0) _speed.y += 0.05;
}

//������̈ړ��ʂ̌v�Z
void Item::vecKeisan(Vec2 touchPos, float windRange, float windBoost, float actionTime)
{
	//���ۈړ���
	float vecPulus = 0.0f;
	//�K�p�͈�
	float hani = windRange;

	_windBoost = windBoost;

	//�ړ��l�̌v�Z
	if ((sqrt(
		pow(touchPos.x - getPositionX(), 2) +
		pow(touchPos.y - getPositionY(), 2)))
		<= hani)
	{
		//if (!_isWind)kazekaiten(actionTime);
		//{
		vecPulus = _maxSpeed * _windBoost *
			(hani - (sqrt(
				pow(touchPos.x - getPositionX(), 2) +
				pow(touchPos.y - getPositionY(), 2))))
			/ hani;


		//�p�x�̌v�Z
		float angle = atan2(getPositionY() - touchPos.y, getPositionX() - touchPos.x);
		//�ړ��ʂ̓K�p
		_speed = Vec2(vecPulus * cos(angle), vecPulus * sin(angle));

	}

	//�ړ������̕ύXX
	if (touchPos.x - getPositionX() <= 0)_isGoRight = true;
	else _isGoRight = false;

	//�ړ������̕ύXY
	if (touchPos.y - getPositionY() >= 0)_isGoDown = true;
	else _isGoDown = false;
	setNoOverMaxSpeed();
}

void Item::setNoOverMaxSpeed()
{

	//y����-------------------------------------------------------------------

	if (!_isGoDown &&_speed.y >= _maxSpeed * _windBoost)//�����
	{
		_speed.y = _maxSpeed * _windBoost;
	}

	else if (_isGoDown &&_speed.y <= -_maxSpeed * _windBoost)//������
	{
		_speed.y = -_maxSpeed * _windBoost;
	}
	//------------------------------------------------------------------------

	//x����-------------------------------------------------------------------

	if (_isGoRight && _speed.x >= _maxSpeed * _windBoost)
	{
		_speed.x = _maxSpeed * _windBoost;
	}
	else if (!_isGoRight && _speed.x <= -_maxSpeed * _windBoost)
	{
		_speed.x = -_maxSpeed * _windBoost;
	}
}
