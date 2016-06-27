#ifndef  _StageKusa_H_
#define  _StageKusa_H_

#include "cocos2d.h"
#include "MultiResolution.h"
using namespace cocos2d;
using namespace std;

class StageKusa : public Node
{

public:
	static StageKusa *create();
	bool init();
	void update(float dt);
	void kazePatapata(Sprite *targetKusa, bool isLeft,float delayTime, float caleCnt);
	void kazeAtariKeisan(Vec2 touchStartPos, float windRange, float kumomoAngle, float caleCnt, int haniAngle);
	void itumonoPatapata(Sprite * targetKusa, bool isLeft);
	Vector<Sprite*> _kusaSozai;


};

#endif
