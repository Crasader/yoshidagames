#include "Enemy.h"

bool Enemy::init(const char *fileName, int maxSpeed, float gravity, bool isYanki, int myNo)
{
	if (!Sprite::init())return false;
	initWithFile(fileName);
	setScale(0.2f);
	//�d�͂̒l
	_gSpeed = gravity;
	//�v���C���[�̑��x
	_pSpeed = Vec2(0, _gSpeed);
	//�E�����Ɍ������Ă��邩
	_isGoRight = true;
	//�������Ɍ������Ă��邩
	_isGoDown = true;
	//�^�b�`���Ă��邩	
	_isWind = false;
	//�S�[���������ǂ���
	_isGool = false;
	//��񂫁[���ǂ���
	_isYanki = isYanki;
	//�����̔ԍ�(�i�j�c����Ȃ̂��̔ԍ�)
	_myNo = myNo;
	//�ő�ړ����x
	_maxSpeed = maxSpeed;

	//�X�e�[�W���ł̍ő�ړ��ʁiX�����j
	_moveMaxX = (designResolutionSize.width * 2) - 100;

	// update�𖈃t���[�����s����悤�ɓo�^����
	this->scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	if (!_isGool)speedKeisan();
	if (_isWind)rotateKeisan();
}
