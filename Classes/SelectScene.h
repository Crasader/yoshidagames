#ifndef __Yoshida__SelectScene__
#define __Yoshida__SelectScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FLayer.h"

using namespace cocos2d;
using namespace std;

class SelectScene : public FLayer
{
public:
	static Scene *createScene();
	static SelectScene *create();
	virtual bool init();
	void update(float delta);

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);

	vector<Sprite*> _uekibati;
	Sprite * _yoshida;
	Sprite * _kumomo;

	Vec2 _touchStartPos;
};

#endif /* defined(__Yoshida__SelectScene__) */