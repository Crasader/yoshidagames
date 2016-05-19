//prototype create yoshidasan
//
//create by kagihiro
//
//16/05/05


#ifndef  __Kusahayasu_H_
#define  __Kusahayasu_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

#include "ResultScene.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
class Kusahayasu : public Node
{
public:
	static Kusahayasu* create();
	bool init();
	void update(float dt);
	
	void kusahayasu(Vec2 hayasuPos,int hayasuNam);
	void scorePlus(int myNum);

	int _score;
	vector<Sprite*> _kusa;

	void goResult();

	bool _isChangeScene;

	int _goalYoshida;
	int _goalGirl;
	int _goalDebu;
	int _goalYanki;
};
#endif
