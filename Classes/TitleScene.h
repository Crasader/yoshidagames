#ifndef __Yoshida__TitleScene__
#define __Yoshida__TitleScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FLayer.h"

#include "Yoshidasan.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class TitleScene : public FLayer
{
public:
	static Scene *createScene();
	static TitleScene *create();
	virtual bool init();
	void update(float delta);
	void kusahayasu();

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);

	void touchAction();

	bool _isChangeScene;
	bool _start;

	Sprite *_yoshida;
	Sprite *_kumo;
	Sprite * _yubi;
	Vector<Sprite*> _kusaSozai;

	float _startX;
};

#endif /* defined(__Yoshida__TitleScene__) */
