//
//__KButton__
//
//create by kagihiro
//
//2016/04/11
//
//�摜�ƃ{�^�����������Ƃ��̏�������������{�^���ɂ���N���X
//�g�p��
//
//Scene�����N���X�ɍs��
//-----------------------------------------------------------------
//KButton *kButton = KButton::getInstance();
//kButton->removeChild();
//addChild(kButton);
//kButton->buttonClear();
//------------------------------------------------------------------
//
//�{�^���̒ǉ��������N���X�ł����Ȃ�
//------------------------------------------------------------------
//function<void(Sprite *sp)>func = [=](Sprite *sp)
//	{
//		��肽������(�����͕K��Sprite *sp�ɂ��Ȃ��ƃG���[���N����)
//	};
//��sp�͓�������Sprite���Ԃ��Ă���
//KButton *kButton = KButton::getInstance();
//kButton->setButton(�摜, func);
//-------------------------------------------------------------------
//



#ifndef __KButton_CPP__H__
#define __KButton_CPP__H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class KButton :public Node
{
public:
	KButton();
	~KButton();
	virtual bool init();
	static KButton *_instance;
	static KButton *getInstance();
	void setButton(Sprite *sprite, function<void(Sprite *sp)> func);
	// �^�b�`�C�x���g����
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void buttonClear();
	int getButtonNum();
	void removeChild();
private:
	//�{�^�������ۑ�
	vector<function<void(Sprite *sp)>> _buttonFunc;
	//�{�^���X�v���C�g
	vector<Sprite*> _buttonSprite;
	//�^�b�`�����X�v���C�g
	Sprite *_isTouchSprite;
	//�^�b�`�����X�v���C�g�̔ԍ�
	int _isTouchNum;
	
};
#endif