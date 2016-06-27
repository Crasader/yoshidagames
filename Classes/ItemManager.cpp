#include "ItemManager.h"

//ItemManager *ItemManager::create()
//{
//
//	ItemManager *pRet = new ItemManager();
//	if (pRet && pRet->init(nullptr))
//	{
//		pRet->autorelease();
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = NULL;
//		return NULL;
//	}
//}


bool ItemManager::init()
{
	if (!Node::init())return false;

	//�����������ɓn���X�s�[�h�̊��� speed/_speedtyousei
	_speedtyousei = 4.0f;

	_touchStartPos = Vec2(0, 0);
	_yoshidaCenterPos = Vec2(0, 0);
	_taisyouItem.clear();
	_kumomoAngle = 0.0f;
	_haniAngle = 0;

	_windRange = 0.0f;
	_windCallCnt = 0.0f;

	Stone *stone1 = new Stone();
	stone1->init();
	stone1->autorelease();
	stone1->setPosition(Vec2(designResolutionSize.width*0.3f, designResolutionSize.height*0.3f));
	addChild(stone1);
	_itemArr.push_back(stone1);

	this->scheduleUpdate();

	return true;
}

void ItemManager::update(float dt)
{
	if (_windCallCnt > 0)
	{
		_windCallCnt -= dt;
		kazeKeisan();
	}
}

void ItemManager::touchEndCall(int haniAngle, float windRange, float angle, Vec2 touchStartPos, Vec2 windEndPos, float windTime)
{
	_touchStartPos = touchStartPos;
	_windRange = windRange;
	_haniAngle = haniAngle;
	_kumomoAngle = angle;
	_touchStartPos = touchStartPos;
	_windCallCnt = windTime;

	angle = angle * 180 / M_PI;
	for (auto item : _itemArr)
	{
		item->_isWind = false;
	}
}

void ItemManager::kazeKeisan()
{
	_taisyouItem.clear();

	//���M���M����
	if (_kumomoAngle > 180 - _haniAngle)
	{
		float overAngle = _haniAngle - 180 + _kumomoAngle;

		//�͈͓��̃A�C�e���̔ԍ����擾
		for (int i = 0; i < _itemArr.size(); i++)
		{
			float itemAngle = atan2(_itemArr.at(i)->getPositionY() - _touchStartPos.y, _itemArr.at(i)->getPositionX() - _touchStartPos.x)* 180.0f / M_PI;

			if ((itemAngle >= _kumomoAngle - _haniAngle && itemAngle <= _kumomoAngle + _haniAngle) ||
				(itemAngle <= -180.0f + overAngle && itemAngle >= -180.0f))
			{
				_taisyouItem.push_back(i);
			}
		}
	}

	//���M���M����
	else if (_kumomoAngle < -180 + _haniAngle)
	{
		float overAngle = -_haniAngle + 180 + _kumomoAngle;

		for (int i = 0; i < _itemArr.size(); i++)
		{
			float itemAngle = atan2(_itemArr.at(i)->getPositionY() - _touchStartPos.y, _itemArr.at(i)->getPositionX() - _touchStartPos.x)* 180.0f / M_PI;
			if ((itemAngle >= _kumomoAngle - _haniAngle && itemAngle <= _kumomoAngle + _haniAngle) ||
				(itemAngle >= 180.0f + overAngle && itemAngle <= 180.0f))
			{
				_taisyouItem.push_back(i);
			}
		}
	}

	//���̑�
	else
	{
		for (int i = 0; i < _itemArr.size(); i++)
		{
			float itemAngle = atan2(_itemArr.at(i)->getPositionY() - _touchStartPos.y, _itemArr.at(i)->getPositionX() - _touchStartPos.x)* 180.0f / M_PI;
			if (itemAngle >= _kumomoAngle - _haniAngle && itemAngle <= _kumomoAngle + _haniAngle)
			{
				_taisyouItem.push_back(i);
			}
		}
	}

	for (int i = 0; i < _taisyouItem.size(); i++)
	{
		_itemArr.at(_taisyouItem[i])->vecKeisan(_touchStartPos, _windRange * (_windMaxTime - _windCallCnt) / _windMaxTime, _windCallCnt);
	}
}

void ItemManager::itemCreate(Vec2 itemPos,Node target,int ItemNo) 
{
	const char * itemPas;
	float gravity = -1.0f;

	switch (ItemNo)
	{
	case 0://������
		itemPas = "pix/stageSozai/windmill.png";
		gravity *= 0.0f;
		break;
	case 1://��
		itemPas = "pix/actor/yoshidagirl.png";
		gravity *= 0.8f;
		break;
	case 2://�ł�
		itemPas = "pix/actor/yoshidadebu.png";
		gravity *= 1.1f;
		break;
	case 3://�����L�[
		itemPas = "pix/actor/yoshidasanyanki.png";
		gravity *= 1.0f;
		break;
	default://�ی�
		itemPas = "pix/actor/yoshidasan.png";
		gravity *= 1.0f;
		break;
	}
}