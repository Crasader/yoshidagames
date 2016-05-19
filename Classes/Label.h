//
//  Label.h
//  TextScript1
//
//  Created by Furukawa on 2014/10/28.
//
//

#ifndef __TextScript1__Label__
#define __TextScript1__Label__

#include <stdio.h>
#include "cocos2d.h"
#include "MultiResolution.h"

using namespace std;
using namespace cocos2d;

namespace nicos2d
{
    class Label: public cocos2d::Label
    {
    public:
        bool init(string str, string fontFile, int fontSize);
        static nicos2d::Label *create(string str, string fontFile, int fontSize);
        void update(float delta);
        
        void startRunString(string text, float dt);
        void endRunString();
        
        bool getRunning(){return running;};
        float delayTime;
        
        static const int STRING_LINE_MAX;
        
        string talkingChar;
        
    private:
        
        int frameCnt;
        string baseString;
        int tempDelayTime;
        
        int lineCount;
        
        bool running;
        bool cansel;
        
        void runString();
        
    protected:
        
        
    };
}

#endif /* defined(__TextScript1__Label__) */
