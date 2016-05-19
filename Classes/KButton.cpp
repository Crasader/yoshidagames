//
//__KButton__
//
//create by kagihiro
//
//2016/04/11
//

#include "KButton.h"

KButton *KButton::_instance;

KButton::KButton()
{
}

KButton::~KButton()
{
}

//�V���O���g���ɂ���
KButton *KButton::getInstance()
{
	//_instance������Ă��Ȃ����������
	if (_instance == NULL)
	{
		_instance = new KButton();
		_instance->init();
	}

	return _instance;
}

bool KButton::init()
{
	if (!Node::init())return false;

	// �^�b�`�C�x���g��L���ɂ���
	// �^�b�`���ꂽ���Ƃ��擾����I�u�W�F�N�g
	auto listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->setSwallowTouches(true);
	// �^�b�`���ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchBegan = CC_CALLBACK_2(KButton::onTouchBegan, this);
	// �^�b�`���������u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchMoved = CC_CALLBACK_2(KButton::onTouchMoved, this);
	// �^�b�`�������ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchEnded = CC_CALLBACK_2(KButton::onTouchEnded, this);
	// �C�x���g�̎��s�̗D�揇�ʂ��m�[�h�̏d�Ȃ菇�Ɉˑ�������
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//�^�b�`���ꂽ�X�v���C�g�ۑ�
	_isTouchSprite = NULL;

	//�^�b�`���ꂽ�X�v���C�g�ۑ��̔ԍ�
	_isTouchNum = -1;

	return true;
}

//----------------------------------------------------------------------------------------------------------------
// �^�b�`�����u�ԂɌĂ΂�郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
bool KButton::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (_isTouchNum < 0)
	{

		Point touchPoint = Vec2(pTouch->getLocationInView().x, pTouch->getLocationInView().y);
		touchPoint.y = designResolutionSize.height - touchPoint.y;

		//�e�R�}���h
		for (int i = 0; i < _buttonSprite.size(); i++)
		{
			Rect spriteRect = _buttonSprite[i]->boundingBox();
			if (spriteRect.containsPoint(touchPoint))
			{
				Vec2 buttonVec = _buttonSprite[i]->getPosition();
				_buttonSprite[i]->setPosition(Vec2(buttonVec.x, (buttonVec.y - 10)));
				_buttonSprite[i]->setColor(Color3B(150, 150, 150));
				_isTouchSprite = _buttonSprite[i];
				_isTouchNum = i;
				break;
			}
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------
// �^�b�`����Ă��鎞�ɌĂ΂�郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
void KButton::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	if (_isTouchNum >= 0)
	{
		Point touchPoint = Vec2(pTouch->getLocationInView().x, pTouch->getLocationInView().y);
		touchPoint.y = designResolutionSize.height - touchPoint.y;
		Rect spriteRect = _isTouchSprite->boundingBox();

		if (!(spriteRect.containsPoint(touchPoint)))
		{
			Vec2 buttonVec = _isTouchSprite->getPosition();
			_isTouchSprite->setPosition(Vec2(buttonVec.x, (buttonVec.y + 10)));
			_isTouchSprite->setColor(Color3B(255, 255, 255));
			_isTouchSprite = _isTouchSprite;
			_isTouchSprite = NULL;
			_isTouchNum = -1;
		}
	}
}


//----------------------------------------------------------------------------------------------------------------
// �^�b�`�������ꂽ���ɂ�΂�郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
void KButton::onTouchEnded(Touch* pTouch, Event* pEvent)
{

	if (_isTouchNum>=0)
	{
		Vec2 buttonVec = _isTouchSprite->getPosition();
		_isTouchSprite->setPosition(Vec2(buttonVec.x, (buttonVec.y + 10)));
		_isTouchSprite->setColor(Color3B(255, 255, 255));
		_isTouchSprite = _isTouchSprite;
		_buttonFunc[_isTouchNum](_isTouchSprite);
		_isTouchSprite = NULL;
		_isTouchNum = -1;

	}
}

//----------------------------------------------------------------------------------------------------------------
// �{�^�����^�b�`���郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
void KButton::setButton(Sprite * sprite, function<void(Sprite *sp)> func)
{
	_buttonFunc.push_back(func);
	_buttonSprite.push_back(sprite);
}

//----------------------------------------------------------------------------------------------------------------
// �{�^�����������郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
void KButton::buttonClear()
{
	_buttonFunc.clear();
	_buttonSprite.clear();
}

//----------------------------------------------------------------------------------------------------------------
// �{�^�����̐��𐔂��郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
int KButton::getButtonNum()
{
	return _buttonFunc.size();
}

//----------------------------------------------------------------------------------------------------------------
// �{�^���𗣉����郁�\�b�h
//----------------------------------------------------------------------------------------------------------------
void KButton::removeChild()
{
	if(getParent() !=NULL)removeFromParent();
}

