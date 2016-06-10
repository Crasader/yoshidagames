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



	this->scheduleUpdate();

	return true;
}

void ItemManager::update(float dt)
{

}