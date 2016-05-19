//----------------------------------------------------------------------------------------------------------------
// �e���v���[�g�V�[���N���X
// �R�s�y�p
// templateScene.h
// CopyWright Ken.D.Ohishi 2015.11.07
//----------------------------------------------------------------------------------------------------------------
#ifndef __TEMPLATE_SCENE_H__
#define __TEMPLATE_SCENE_H__

#include "cocos2d.h"

//----------------------------------------------------------------------------------------------------------------
// TemplateScene�N���X�̒�`�F�V�[���N���X��Layer�N���X���p������
//----------------------------------------------------------------------------------------------------------------
class TemplateScene : public cocos2d::Layer
{
protected:
	TemplateScene();							// �R���X�g���N�^
	virtual ~TemplateScene();					// �f�X�g���N�^

	virtual bool init();						// ������
	virtual void update(float dt);				// �X�V
	virtual void onEnterTransitionDidFinish();	// 

	// �^�b�`�C�x���g����
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

public:											
	static cocos2d::Scene* createScene();		// 

	CC_SYNTHESIZE(bool, _isTouch, IsTouch);				// �^�b�`����t���O
	CC_SYNTHESIZE(unsigned int, _frameCnt, FrameCnt);	// �t���[���J�E���^�[

	// create���\�b�h�������I�ɍ쐬����d�g�݁i�R���r�j�G���X�R���X�g���N�^�j
	CREATE_FUNC(TemplateScene);

};

#endif // __TEMPLATE_SCENE_H__
