//prototype create yoshidasan
//
//create by kagihiro
//
//IyanaYatsu
//16/07/5

#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "Yoshidasan.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
class IyanaYatsu : public Node
{
public:
	static IyanaYatsu* create(Vec2 bornPos);
	bool init(Vec2 bornPos);
	void update(float dt);
	void headRotateSet(float rotate);
	void kazehukasu(Vector<Yoshidasan*> yoshida);
	Sprite *_body;
	Sprite *_head;


};

