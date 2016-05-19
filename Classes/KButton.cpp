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

//シングルトンにする
KButton *KButton::getInstance()
{
	//_instanceが作られていなかったらつくる
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

	// タッチイベントを有効にする
	// タッチされたことを取得するオブジェクト
	auto listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->setSwallowTouches(true);
	// タッチされた瞬間に呼ばれるメソッドを登録
	listener->onTouchBegan = CC_CALLBACK_2(KButton::onTouchBegan, this);
	// タッチが動いた瞬間に呼ばれるメソッドを登録
	listener->onTouchMoved = CC_CALLBACK_2(KButton::onTouchMoved, this);
	// タッチが離された瞬間に呼ばれるメソッドを登録
	listener->onTouchEnded = CC_CALLBACK_2(KButton::onTouchEnded, this);
	// イベントの実行の優先順位をノードの重なり順に依存させる
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//タッチされたスプライト保存
	_isTouchSprite = NULL;

	//タッチされたスプライト保存の番号
	_isTouchNum = -1;

	return true;
}

//----------------------------------------------------------------------------------------------------------------
// タッチした瞬間に呼ばれるメソッド
//----------------------------------------------------------------------------------------------------------------
bool KButton::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (_isTouchNum < 0)
	{

		Point touchPoint = Vec2(pTouch->getLocationInView().x, pTouch->getLocationInView().y);
		touchPoint.y = designResolutionSize.height - touchPoint.y;

		//各コマンド
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
// タッチされている時に呼ばれるメソッド
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
// タッチが離された時によばれるメソッド
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
// ボタンをタッチするメソッド
//----------------------------------------------------------------------------------------------------------------
void KButton::setButton(Sprite * sprite, function<void(Sprite *sp)> func)
{
	_buttonFunc.push_back(func);
	_buttonSprite.push_back(sprite);
}

//----------------------------------------------------------------------------------------------------------------
// ボタンを消去するメソッド
//----------------------------------------------------------------------------------------------------------------
void KButton::buttonClear()
{
	_buttonFunc.clear();
	_buttonSprite.clear();
}

//----------------------------------------------------------------------------------------------------------------
// ボタンをの数を数えるメソッド
//----------------------------------------------------------------------------------------------------------------
int KButton::getButtonNum()
{
	return _buttonFunc.size();
}

//----------------------------------------------------------------------------------------------------------------
// ボタンを離縁するメソッド
//----------------------------------------------------------------------------------------------------------------
void KButton::removeChild()
{
	if(getParent() !=NULL)removeFromParent();
}

