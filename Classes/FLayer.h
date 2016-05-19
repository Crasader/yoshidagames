//
//  FLayer.h
//  Collapse
//
//  Created by Furukawa on 2015/11/20.
//
//

#ifndef __Collapse__FLayer__
#define __Collapse__FLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class FLayer : public Layer
{
public:
    static Scene *createScene();
    static FLayer *create();
    virtual bool init();
    virtual void update(float delta);
    
    
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* unused_event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);
    
    
    
    cocos2d::Vec2 _touchPos;
    bool _isTouch;
    
    int _frameCnt;
    
};

#endif /* defined(__Collapse__FLayer__) */
