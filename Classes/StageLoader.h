//prototype create yoshidasan
//
//create by kagihiro
//
//16/06/06

#ifndef __StageLoader_H__
#define __StageLoader_H__
#include "cocos2d.h"
#include "MultiResolution.h"
using namespace std;
using namespace cocos2d;

class StageLoader : public Node
{
public:
	static StageLoader *create();
	bool init();
	//ファイル読み込み
	void loadStringFromFile(string fileName);
	//読み込んだitemを返す
	vector<vector<string>> getItem();
	//読み込んだstageを返す
	vector<vector<string>> getStage();


	//itemデータ
	vector<vector<string>> _itemData;
	//stageデータ
	vector<vector<string>> _stageData;

};

#endif

