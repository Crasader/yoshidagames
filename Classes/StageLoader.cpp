#include "StageLoader.h"

StageLoader * StageLoader::create()
{

	StageLoader *pRet = new StageLoader();
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

bool StageLoader::init()
{
	if (!Node::init()) return false;
	return true;
}

void StageLoader::loadStringFromFile(string fileName)
{



	_itemData.clear();
	_stageData.clear();

	auto fileText = FileUtils::getInstance()->getStringFromFile(fileName);

	//中身保存用
	vector<string> naiyou;
	naiyou.clear();

	//何のオブジェクトか保存用
	string key;
	key.clear();

	//スラシュ保存用
	string slash;
	slash.clear();

	enum DataType
	{
		HANTEI = 0,
		KEY_ITEM,
		KEY_STAGE,
		ITEM,
		STAGE,
		COMMENTOUT,

	};

	DataType type = HANTEI;

	//$ITEM,#STAGE
	for (char c : fileText)
	{
		if (c == '\r')continue;
		switch (type)
		{
		case HANTEI:
			if (c == '\n')continue;
			else if (c == '$')
			{
				type = KEY_ITEM;
				continue;
			}
			else if (c == '#')
			{
				type = KEY_STAGE;
				continue;
			}
			else if (c == '/')
			{
				slash.push_back(c);
				if (slash == "//")
				{
					slash.clear();
					type = COMMENTOUT;
				}
				continue;
			}
			break;
		case KEY_ITEM:
			if (c == ',')
			{
				naiyou.push_back(key);
				key.clear();
				type = ITEM;
				continue;
			}
			key.push_back(c);
			break;
		case KEY_STAGE:
			if (c == ',')
			{
				naiyou.push_back(key);
				key.clear();
				type = ITEM;
				continue;
			}
			key.push_back(c);
			break;
		case ITEM:
			if (c == '\n') 
			{
				naiyou.push_back(key);
				key.clear();
				_itemData.push_back(naiyou);
				naiyou.clear();
				type = HANTEI;
				continue;
			}
			key.push_back(c);
			break;
		case STAGE:
			if (c == '\n')
			{
				naiyou.push_back(key);
				key.clear();
				_stageData.push_back(naiyou);
				naiyou.clear();
				type = HANTEI;
				continue;
			}
			key.push_back(c);
			break;
		case COMMENTOUT:
			if (c == '\n')
			{
				type = HANTEI;
			}
			break;
		default:
			break;
		}
	}
}

vector<vector<string>> StageLoader::getItem()
{
	return _itemData;
}

vector<vector<string>> StageLoader::getStage()
{
	return _stageData;
}




