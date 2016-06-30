#ifndef __Yoshida__ResultScene__
#define __Yoshida__ResultScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FLayer.h"

using namespace cocos2d;
//using namespace extension;
//using namespace CocosDenshion;
using namespace std;

class ResultScene : public FLayer
{
public:
	static Scene *createScene(int yoshida, int girl, int debu, int yanki);
	static ResultScene *create(int yoshida, int girl, int debu, int yanki);
	virtual bool init(int yoshida, int girl, int debu, int yanki);
	void update(float delta);
	bool onTouchBegan(Touch *touch, Event *event);
	void mojitukuru(Vec2 hyoujiPos, string hyoujiMozi, const char* hyoujiFont,int hyoujiSize, bool isRight);

	float _score;

	int _mojiFontSize;
	int _suujiFontsize;

	bool _changeScene;

	const char * _mojiFontPas;
	const char * _suujiFontPas;
	

};

#endif /* defined(__Yoshida__ResultScene__) */
