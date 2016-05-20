//
//  EffectManager.cpp
//  StreamTest
//
//  Created by Shimada on 2016/04/11.
//
//

#include "EffectManager.h"

EffectManager *EffectManager::create()
{
	EffectManager *pRet = new EffectManager();
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

bool EffectManager::init()
{
	if (!Layer::init()) return false;


	return true;
}

//�L���L�������ʂ���юU��
void EffectManager::touchEffectCreate(Vec2 Pos) 
{
	int kirakiraDeru = 20;
	for (int i = 0; i<kirakiraDeru; i++)
	{
		_kirakira = Sprite::create("pix/eff/maru.png");
		_kirakira->setTextureRect(Rect(0, 0, 32, 32));
		_kirakira->setColor(Color3B(255, 255, 100));
		//CCLOG("%f",Pos);
		_kirakira->setPosition(Pos);
		_kirakira->setScale(3);
		_kirakira->setColor(Color3B(155 + rand()%100,
			                        155 + rand()%100,
                                    155 + rand()%100));
		addChild(_kirakira);

		//srand((unsigned)time(NULL));
		//float ran = rand() % 100;

		// �J���t���{�[���������_���ɔz�u����
		int width = -200 + (rand() % 400);//((int)designResolutionSize.width + 100));
		int height = -200 + (rand() % 400);//((int)designResolutionSize.height + 100));

		// �J���t���{�[���������_���ȕ����֓��߂����Ȃ���ړ�������
		auto act1 = RotateTo::create(1.0f, 270.0f);				// 270�x��]�����ʒu�Ŏ~�܂�
		auto act2 = MoveBy::create(1.0f, Vec2(width, height));	//����
		auto act3 = FadeOut::create(1.0f);						//���񂾂������
		auto act4 = ScaleBy::create(1.0f,0.2);						//�������Ȃ�
		auto spawn = Spawn::create(act1, act2, act3,act4, nullptr);	// �A�N�V�����𓯎��Ɏ��s
		auto act5 = RemoveSelf::create();						// �������g���폜
		auto sequence = Sequence::create(spawn, act5, nullptr); // �A�N�V���������ԂɎ��s
		_kirakira->runAction(sequence);
	}
}

//�킽�������U����(�����ʂ���юU��)
void EffectManager::watageBakusan(Vec2 bakusanPos) 
{
	int kirakiraDeru = 10;
	int hani = 50;
	for (int i = 0; i<kirakiraDeru; i++)
	{
		_kirakira = Sprite::create("pix/eff/maru.png");
		_kirakira->setTextureRect(Rect(0, 0, 32, 32));
		_kirakira->setColor(Color3B(255, 255, 255));
		//CCLOG("%f",Pos);
		_kirakira->setPosition(bakusanPos);
		//_kirakira->setScale(3);
		addChild(_kirakira);

		//srand((unsigned)time(NULL));
		//float ran = rand() % 100;

		// �J���t���{�[���������_���ɔz�u����
		int width = -hani + (rand() % (hani* 2));//((int)designResolutionSize.width + 100));
		int height = -hani + (rand() % (hani * 2));//((int)designResolutionSize.height + 100));

										   // �J���t���{�[���������_���ȕ����֓��߂����Ȃ���ړ�������
		auto act1 = RotateTo::create(1.0f, 270.0f);				// 270�x��]�����ʒu�Ŏ~�܂�
		auto act2 = MoveBy::create(1.0f, Vec2(width, height));	//����
		auto act3 = FadeOut::create(1.0f);						//���񂾂������
		auto act4 = ScaleBy::create(1.0f, 0.2);						//�������Ȃ�
		auto spawn = Spawn::create(act1, act2, act3, act4, nullptr);	// �A�N�V�����𓯎��Ɏ��s
		auto act5 = RemoveSelf::create();						// �������g���폜
		auto sequence = Sequence::create(spawn, act5, nullptr); // �A�N�V���������ԂɎ��s
		_kirakira->runAction(sequence);
	}
}

//�g���ɍL����
void EffectManager::hamonCreate(Vec2 Pos)
{
	_hamon = Sprite::create("pix/eff/maru.png");
	_hamon->setScale(2.0);
	_hamon->setPosition(Pos);
	addChild(_hamon);

	// �t�F�[�h�A�E�g
	auto act1 = FadeOut::create(0.5f);				//���񂾂�����Ă���
	auto act2 = ScaleTo::create(0.5f, 3.0);			//�傫������
	auto spawn = Spawn::create(act1, act2, nullptr);	// �A�N�V�����𓯎��Ɏ��s
	auto act4 = RemoveSelf::create();						// �������g���폜
	auto sequence = Sequence::create(spawn, act4, nullptr); // �A�N�V���������ԂɎ��s
	_hamon->runAction(sequence);
}

//���ɉ������˂����
void EffectManager::hunsyaBusya(Vec2 Pos)
{
	for (int i = 0; i < 30; i++)
	{
		_smoke = Sprite::create("pix/eff/busya_e.png");
		_smoke->setPosition(Pos);
		int col = (rand() % 15);
		_smoke->setScale(0.8);
		_smoke->setColor(Color3B(240 + col, 240 + col, 255));
		addChild(_smoke);

		//�����_���ɔz�u����
		float width = -200 + (rand() % 400); //*((rand() % 2 == 0) ? 1 : -1);
		float height = -800 + (rand() % 300);
		float speed = (rand() % 100 / 50) * 1 + 1.0;


		// �����_���ȕ����֓��߂����Ȃ���ړ�������
		// �W�����v�̃A�N�V����
		auto act1 = JumpBy::create(
			speed,          // ����
			Vec2(width, height - 30), // ���n���W
			height,        // ����
			1              // ��
			);
		auto act2 = FadeOut::create(speed);						//���񂾂������
		auto spawn = Spawn::create(act1, act2, nullptr);	// �A�N�V�����𓯎��Ɏ��s
		auto act3 = RemoveSelf::create();						// �������g���폜
		auto act4 = DelayTime::create((rand() % 80 / 100.0f));
		auto sequence = Sequence::create(act4, spawn, act3, nullptr); // �A�N�V���������ԂɎ��s
		_smoke->runAction(sequence);
	}
}

//�n�`�݂����ȋO�Ղ��o��
void EffectManager::createBokujyu(Vec2 Pos)
{
	int kirasuu = 30;
	float actionTime = 0.5f;
	for (int i = 0; i < kirasuu; i++)
	{
		Sprite * kirakira = Sprite::create();
		int kiraSize = random(10, 30);
		kirakira->setTextureRect(Rect(0, 0, kiraSize, kiraSize));
		Vec2 kirarandmPos = Vec2(random(-20, 20), random(-20, 20));
		kirakira->setPosition(Pos + kirarandmPos);
		//kirakira->setColor(Color3B(random(150,250), random(150, 250), random(150, 250)));
		kirakira->setColor(Color3B::BLACK);
		addChild(kirakira);

		Vec2 kirakirandm = Vec2(random(-20, 20), random(-20, 20));
		auto move = MoveBy::create(actionTime, kirakirandm);
		auto eOutMove = EaseOut::create(move, 3);
		auto mini = ScaleTo::create(actionTime, 0.0f);
		auto kaiten = RotateBy::create(actionTime, 200);
		auto mazeru = Spawn::create(eOutMove, mini, kaiten, nullptr);
		auto desh = RemoveSelf::create();
		auto seq = Sequence::create(mazeru, desh, nullptr);
		kirakira->runAction(seq);
	}
}