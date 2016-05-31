#include "Enemy.h"

bool Enemy::init(const char *fileName, int maxSpeed, float gravity, bool isYanki, int myNo)
{
	if (!Sprite::init())return false;
	initWithFile(fileName);
	setScale(0.2f);
	//�d�͂̒l
	_gSpeed = 0;
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

	_speed = 1.2;

	//�X�e�[�W���ł̍ő�ړ��ʁiX�����j
	_moveMaxX = (designResolutionSize.width * 2) - 100;

	//��ԋ߂��g�c����̏ꏊ
	_yoshidaPos = Vec2(0,0);

	// update�𖈃t���[�����s����悤�ɓo�^����
	this->scheduleUpdate();

	return true;
}

void Enemy::update(float dt)
{
	if (!_isGool)speedKeisan();
	if (_isWind)rotateKeisan();
	enemyMove();
}

void Enemy::enemyMove() 
{
	Vec2 myPos = getPosition();
	Vec2 a = _yoshidaPos - myPos;
	float kyori = sqrt(pow(a.x, 2) + pow(a.y, 2));
	Vec2 idou = Vec2((a.x/kyori) *_speed, (a.y/kyori) * _speed);
	//Vec2 idou = Vec2(_speed,_speed);
	setPosition(myPos + idou);
}
