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
	void kazePatapata(Sprite *targetKusa, bool _isLeft);
	void kazeAtariKeisan(Vec2 touchStartPos, float kumomoAngle, int haniAngle);
	Vector<Sprite*> _kusaSozai;


};

#endif
