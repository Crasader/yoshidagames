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
	//�t�@�C���ǂݍ���
	void loadStringFromFile(string fileName);
	//�ǂݍ���item��Ԃ�
	vector<vector<string>> getItem();
	//�ǂݍ���stage��Ԃ�
	vector<vector<string>> getStage();


	//item�f�[�^
	vector<vector<string>> _itemData;
	//stage�f�[�^
	vector<vector<string>> _stageData;

};

#endif

