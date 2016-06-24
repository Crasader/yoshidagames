//prototype create yoshidasan
//
//create by kagihiro
//
//16/04/22


#ifndef  _APP_Yoshidasan_H_
#define  _APP_Yoshidasan_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class Yoshidasan :public Sprite
{
public:
	virtual bool init(const char *fileName, int maxSpeed, float gravity, bool isYanki,int myNo);
	void update(float dt);
	//������������speed�l�C�h�E
	void speedChange(Vec2 plusSpeed);
	//������̈ړ��ʂ̌v�Z
	void vecKeisan(Vec2 touchPos,float windRange, float actionTime);
	//speed�̓K�p
	void speedKeisan();
	//rotate�̌v�Z
	void rotateKeisan();
	//speed�𔽓]
	void speedFlip();
	//speed�𒲂ׂ�
	Vec2 getSpeed();
	//�ő�X�s�[�ǂɗ}����
	void setNoOverMaxSpeed();
	//����
	void move();
	//�ق��̋g�c�Ɖ�������̃A�N�V����
	void hitAction(Vec2 movePos);

	//�g�c�A�N�V������
	//�n�߂̔�яo��
	void startGo(Vec2 moveState, float dilayTime);
	//�����̗h��
	void actionYuraYura();
	//�ω���߂�
	void allChangeReset();
	//�S�[�[���������̓���
	void actionGoolMove(Vec2 centerPos, float dilay);
	void kazekaiten(float actontime);
	
	void happaPiyon(Vec2 muki);


	bool _isGoRight;
	bool _isGoDown;
	bool _isWind;
	bool _isYanki;
	bool _isGool;
	bool _isRool;
	bool _isHit;

	int _maxSpeed;
	int _myNo;
	float _gSpeed;
	float _moveMaxX;

	Vec2 _pSpeed;
	Rect _goolRect;
	
};

#endif

