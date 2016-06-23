#include "Yoshidasan.h"
#include "YoshidasanNoManager.h"

bool Yoshidasan::init(const char *fileName, int maxSpeed, float gravity, bool isYanki, int myNo)
{
	if (!Sprite::init())return false;
	initWithFile(fileName);
	setScale(0.15f);
	//�d�͂̒l
	_gSpeed = gravity;
	//�v���C���[�̑��x
	_pSpeed = Vec2(0, _gSpeed);
	//�E�����Ɍ������Ă��邩
	_isGoRight = true;
	//�������Ɍ������Ă��邩
	_isGoDown = true;
	//���ɐ�����Ă��邩	
	_isWind = true;
	//�S�[���������ǂ���
	_isGool = false;
	//��񂫁[���ǂ���
	_isYanki = isYanki;
	//�����̔ԍ�(�i�j�c����Ȃ̂��̔ԍ�)
	_myNo = myNo;
	//�ő�ړ����x
	_maxSpeed = maxSpeed;
	//�ق��̋g�c�Ɠ������Ă��邩
	_isHit = false;

	//�X�e�[�W���ł̍ő�ړ��ʁiX�����j
	_moveMaxX = (designResolutionSize.width * 2) - 100;

	// update�𖈃t���[�����s����悤�ɓo�^����
	this->scheduleUpdate();

	return true;
}

void Yoshidasan::update(float dt)
{
	if (!_isGool)speedKeisan();
	//if (_isWind)rotateKeisan();
	move();
}

//������̈ړ��ʂ̌v�Z
void Yoshidasan::vecKeisan(Vec2 touchPos, float windRange, float actionTime)
{
	//���ۈړ���
	float vecPulus = 0.0f;
	//�K�p�͈�
	float hani = windRange;

	//�ړ��l�̌v�Z
	if ((sqrt(
		pow(touchPos.x - getPositionX(), 2) +
		pow(touchPos.y - getPositionY(), 2)))
		<= hani)
	{
		if (!_isWind)kazekaiten(actionTime);
		vecPulus = _maxSpeed *
			((hani -
				sqrt(
					pow(touchPos.x - getPositionX(), 2) +
					pow(touchPos.y - getPositionY(), 2)))
			/ hani) ;


		//�p�x�̌v�Z
		float angle = atan2(getPositionY() - touchPos.y, getPositionX() - touchPos.x);
		//�ړ��ʂ̓K�p
		_pSpeed += Vec2(vecPulus * cos(angle), vecPulus * sin(angle));
	}

	//�ړ������̕ύXX
	if (touchPos.x - getPositionX() <= 0)_isGoRight = true;
	else _isGoRight = false;

	//�ړ������̕ύXY
	if (touchPos.y - getPositionY() >= 0)_isGoDown = true;
	else _isGoDown = false;
	setNoOverMaxSpeed();
}

//������������speed�l�C�h�E
void Yoshidasan::speedChange(Vec2 plusSpeed)
{
	_pSpeed.x += plusSpeed.x;
	_pSpeed.y += plusSpeed.y;

	setNoOverMaxSpeed();
}

//speed�̌v�Z
void Yoshidasan::speedKeisan()
{
	setNoOverMaxSpeed();

	//�d�͂��X�s�[�h�̌����ɂǂ̒��x���f���邩����
	int p = 4;

	//y�����̉^���ʂ̌v�Z-----------------------------------------------------
	if (!_isGoDown)	//�����
	{
		if (_pSpeed.y > _gSpeed)
		{
			_pSpeed.y += _gSpeed / p;
		}
		else
		{
			_pSpeed.y = _gSpeed;
			_isGoDown = true;
		}
	}
	else            //������
	{
		if (_pSpeed.y < _gSpeed)
		{
			_pSpeed.y -= _gSpeed / p;
		}

		else
		{
			_pSpeed.y = _gSpeed;
		}
	}
	//------------------------------------------------------------------------

	//x�����̉^���ʂ̌v�Z-----------------------------------------------------
	if (_pSpeed.x != 0)
	{
		if (_isGoRight)
		{
			if (_pSpeed.x > 0)
			{
				_pSpeed.x += _gSpeed / p;
			}
			else
			{
				_pSpeed.x = 0;
				actionYuraYura();

			}
		}
		else
		{
			if (_pSpeed.x < 0)
			{
				_pSpeed.x -= _gSpeed / p;
			}
			else
			{
				_pSpeed.x = 0;
				actionYuraYura();
			}
		}
	}
	//------------------------------------------------------------------------
}

//rotate�̌v�Z
void Yoshidasan::rotateKeisan()
{
	//�����̊p�x��speed�̃x�N�g������v�Z���ēK�p�@�x = ���W�A�� �~ 180 �� �~���� + 90
	setRotation((atan2(_pSpeed.y, _pSpeed.x) * 180.0f / M_PI) + 90);
	bool xBool = false;
	if (_isYanki) xBool = _isGoRight == _isGoDown;
	else xBool = _isGoRight != _isGoDown;
	setFlipX(xBool);
	setFlipY(!_isGoDown);
}

//speed�𒲂ׂ�
Vec2 Yoshidasan::getSpeed()
{
	return _pSpeed;
}

void Yoshidasan::setNoOverMaxSpeed()
{

	//y����-------------------------------------------------------------------

	if (!_isGoDown &&_pSpeed.y >= _maxSpeed )//�����
	{
		_pSpeed.y = _maxSpeed;
	}

	else if (_isGoDown &&_pSpeed.y <= -_maxSpeed)//������
	{
		_pSpeed.y = -_maxSpeed;
	}
	//------------------------------------------------------------------------

	//x����-------------------------------------------------------------------

	if (_isGoRight && _pSpeed.x >= _maxSpeed)
	{
		_pSpeed.x = _maxSpeed;
	}
	else if (!_isGoRight && _pSpeed.x <= -_maxSpeed)
	{
		_pSpeed.x = -_maxSpeed;
	}
}

void Yoshidasan::move()
{
	//�ړ��ʂ����Z���ăC�h�E
	setPosition(Vec2(getPositionX() + _pSpeed.x, getPositionY() + _pSpeed.y));

	if (getPositionY() < designResolutionSize.height * 0.16f)
	{
		setPositionY(designResolutionSize.height * 0.16f);
		_isWind = false;
		allChangeReset();
	}
}

void Yoshidasan::hitAction(Vec2 movePos)
{
	if (!_isHit)
	{
		stopAllActions();
		_isHit = true;
		auto move = MoveTo::create(0.2f, movePos);
		auto func = CCCallFunc::create([=]()
		{
			_isHit = false;
			actionYuraYura();
		});
		auto seq = Sequence::create(move, func, nullptr);
		runAction(seq);
	}

}

//�����̗h��
void Yoshidasan::actionYuraYura()
{
	stopAllActions();
	setFlipY(false);
	//setFlipX(false);
	auto modosu = RotateTo::create(0.5f, 0);
	auto func = CallFunc::create([=]()
	{
		auto yuraR = RotateBy::create(0.8f, 30);
		auto easeYuraR = EaseInOut::create(yuraR, 2);
		auto yuraL = RotateBy::create(0.8f, -30);
		auto easeYuraL = EaseInOut::create(yuraL, 2);
		auto yura = Sequence::create(easeYuraR, easeYuraL, nullptr);
		auto yurayura = RepeatForever::create(yura);
		runAction(yurayura);
	});
	auto sequence = Sequence::create(modosu, func, nullptr);
	runAction(sequence);

}

//�n�߂̔�яo��
void Yoshidasan::startGo(Vec2 moveState, float dilayTime)
{
	stopAllActions();
	auto  delay = DelayTime::create(dilayTime);
	auto move = MoveBy::create(0.3f, moveState);
	auto func = CallFunc::create([=]()
	{
		actionYuraYura();
		_isWind = false;
	});
	auto sequence = Sequence::create(delay, move, func, nullptr);
	runAction(sequence);

}

//�t���σW�����v�I
void Yoshidasan::happaPiyon(Vec2 muki)
{
	stopAllActions();
	_isGool = true;
	float actionTime = 0.1f;
	int moveKyori = 50;
	auto move = MoveBy::create(actionTime, muki * moveKyori);
	auto moveEI = EaseIn::create(move, 3);
	auto owari = CCCallFunc::create([=]()
	{
		_isGool = false;
		actionYuraYura();
	});
	auto seq = Sequence::create(moveEI, owari, nullptr);
	runAction(seq);

}

//�ω���߂�
void Yoshidasan::allChangeReset()
{
	stopAllActions();
	setFlipY(false);
	//setFlipX(false);
	setRotation(0);
}

//�S�[���������̏���
void Yoshidasan::actionGoolMove(Vec2 centerPos, float dilayTime)
{
	if (!_isGool)
	{
		allChangeReset();
		_isGool = true;
		auto junp = JumpTo::create(dilayTime, centerPos, 100, 1);
		auto kaiten = RotateTo::create(dilayTime, 180.0f);
		auto spw = Spawn::create(junp, kaiten, nullptr);
		auto desu = CallFunc::create([=]()
		{
			YoshidasanNoManager *manager = (YoshidasanNoManager*)getParent();
			manager->yosidaLiveingCheck();
			removeFromParentAndCleanup(true);
		});
		auto seq = Sequence::create(spw, desu, nullptr);
		runAction(seq);
	}
}

void Yoshidasan::kazekaiten(float actontime)
{
	_isWind = true;
	stopAllActions();
	rotateKeisan();
	auto kaiten = RotateBy::create(actontime, 720 * actontime);
	auto eas = EaseOut::create(kaiten, 3);
	auto modmod = RotateTo::create(0.1f, 0);
	auto func = CCCallFunc::create([=]()
	{
		_isWind = false;
	});
	auto seq = Sequence::create(eas, modmod, func, nullptr);
	runAction(seq);
}

//speed�𔽓]
void Yoshidasan::speedFlip()
{
	_pSpeed = -_pSpeed;
	_isGoDown != _isGoDown;
	_isGoRight != _isGoRight;
}

