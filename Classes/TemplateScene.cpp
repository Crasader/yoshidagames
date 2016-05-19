//----------------------------------------------------------------------------------------------------------------
// �e���v���[�g�V�[���N���X
// �R�s�y�p
// TemplateScene.cpp
// CopyWright Ken.D.Ohishi 2015.11.07
//----------------------------------------------------------------------------------------------------------------
#include "TemplateScene.h"

using namespace cocos2d; // cocos2d���ɒ�`����Ă��铯���N���X���iLayer�@Scene���j���`���Ȃ��悤�ɒ���

//----------------------------------------------------------------------------------------------------------------
// Layer��Scene�ɓ\��t���ĕԂ����\�b�h
//----------------------------------------------------------------------------------------------------------------
Scene* TemplateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TemplateScene::create();
	scene->addChild(layer);
	return scene;
}

//----------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------------------------------------------
TemplateScene::TemplateScene()
{
	// �����o�ϐ��̏�����
	_frameCnt = 0;
	_isTouch = false;

}

//----------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------------------------------------------------------------------
TemplateScene::~TemplateScene()
{
	// �����o�ϐ��̉��
}

//----------------------------------------------------------------------------------------------------------------
// �����������F�V�[���i��ʁj�̎��O����
//----------------------------------------------------------------------------------------------------------------
bool TemplateScene::init()
{
	if (!Layer::init())	return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// �^�b�`�C�x���g��L���ɂ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TemplateScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TemplateScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TemplateScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// �V�[�����؂�ւ�������Ƃ��A�����ڂŊm�F�ł���悤�ɁA���x����p��
	auto label = Label::createWithTTF("TemplateScene", "fonts/Marker Felt.ttf", 24);
	label->setPosition(
		Vec2(
			origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height
		)
	);
	this->addChild(label, 1);

	// update�𖈃t���[�����s����悤�ɓo�^����
	this->scheduleUpdate();

	// �t���[���J�E���^�[������
	_frameCnt = 0;

	return true;
}

//----------------------------------------------------------------------------------------------------------------
// ���t���[���Ă΂�鏈��
//----------------------------------------------------------------------------------------------------------------
void TemplateScene::update(float dt)
{
	_frameCnt++;	// �t���[���J�E���^�[�C���N�������g

	CCLOG("cnt = %d", _frameCnt);
	CCLOG("isTouch = %d", _isTouch);

}
//----------------------------------------------------------------------------------------------------------------
// ��ʑJ�ڂ̃g�����W�V�������I�����������ɂP�x�����Ă΂�郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
void TemplateScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();


}

//----------------------------------------------------------------------------------------------------------------
// �^�b�`�����u�ԂɌĂ΂�郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
bool TemplateScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	_isTouch = true;
	Vec2 touchPos = pTouch->getLocation();

	CCLOG("TouchPos = (%f, %f)", touchPos.x, touchPos.y);	// �^�b�`���W���f�o�b�O�\��

	return true;
}

//----------------------------------------------------------------------------------------------------------------
// �^�b�`����Ă��鎞�ɌĂ΂�郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
void TemplateScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	
}

//----------------------------------------------------------------------------------------------------------------
// �^�b�`�������ꂽ���ɂ�΂�郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
void TemplateScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	_isTouch = false;
}
