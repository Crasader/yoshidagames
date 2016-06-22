#include "Kusahayasu.h"
Kusahayasu * Kusahayasu::create()
{


	Kusahayasu *pRet = new Kusahayasu();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}

}

bool Kusahayasu::init()
{
	if (!Node::init())return false;

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadEffect("Pon.mp3");

	_score = 0;

	_goalYoshida = 0;
	_goalGirl = 0;
	_goalDebu = 0;
	_goalYanki = 0;

	_isChangeScene = false;

	_kusa.clear();
	_shiniKusa.clear();
	_hitYoshida.clear();

	this->scheduleUpdate();
	return true;
}

void Kusahayasu::update(float dt)
{

}

void Kusahayasu::kusahayasu(Vec2 hayasuPos)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Pon.mp3");
	Sprite * kusa;

	kusa = Sprite::create("pix/stageSozai/hana.png");
	kusa->setAnchorPoint(Vec2(0.5f, 1.0f));
	addChild(kusa);
	kusa->setPosition(hayasuPos);
	_kusa.push_back(kusa);
	auto up = MoveBy::create(1.0f, Vec2(0, kusa->getBoundingBox().size.height));
	auto eas = EaseOut::create(up, 3);
	kusa->runAction(eas);
}

void Kusahayasu::scorePlus(int myNum)
{
	switch (myNum)
	{
	case 0:
		_goalYoshida++;
		break;
	case 1:
		_goalGirl++;
		break;
	case 2:
		_goalDebu++;
		break;
	case 3:
		_goalYanki++;
		break;
	default:
		break;
	}
	_score++;
}



void Kusahayasu::goResult()
{
	if (!_isChangeScene)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ResultScene::createScene(_goalYoshida, _goalGirl, _goalDebu, _goalYanki)));
		_isChangeScene = true;
	}
}

void Kusahayasu::shiniHayasu(Vec2 shiniPos, int kakudoNum, Node *target)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Pon.mp3");
	Sprite *kusa;
	kusa = Sprite::create("pix/stageSozai/ne.png");
	kusa->setAnchorPoint(Vec2(0.5f, 0.7f));
	kusa->setRotation(90 * kakudoNum);
	target->addChild(kusa,-2);
	kusa->setPosition(shiniPos - target->getPosition());
	kusa->setTag(kakudoNum);
	_shiniKusa.push_back(kusa);
}

vector<Sprite*> Kusahayasu::getShinikusa()
{
	return _shiniKusa;
}

//‰E•Ó(-1.0)¶•Ó(1,0)ã•Ó(0.-1)‰º•Ó(0.1)
void Kusahayasu::kusaHaneAction(Sprite* target,Vec2 muki, Yoshidasan *targetYoshida)
{
	_hitYoshida.push_back(targetYoshida);
	
	if (!(target->numberOfRunningActions()))
	{
		int ugokiti = 10;
		float ugokiJikan = 0.3f;
		auto iku = MoveBy::create(ugokiJikan, muki * ugokiti);
		auto tizi = ScaleTo::create(ugokiJikan, 1 + fabs(muki.y)*0.1f, 1 + fabs(muki.x)*0.1f);
		auto tizimi = Spawn::create(iku, tizi, nullptr);
		auto iitizimi = EaseIn::create(tizimi, 2);

		auto del = DelayTime::create(0.2f);

		auto modo = MoveBy::create(ugokiJikan, -muki * ugokiti);
		auto nobi = ScaleTo::create(ugokiJikan, 1);
		auto nobiru = Spawn::create(modo, nobi, nullptr);
		auto iinobiru = EaseIn::create(nobiru, 2);

		auto func = CCCallFunc::create([=]()
		{
			//for (auto yoshi : _hitYoshida)
			//{
			//	//if (yoshi)targetYoshida->happaPiyon(-muki);
			//}
			//_hitYoshida.clear();
			
		});

		auto seq = Sequence::create(iitizimi,iinobiru,func, nullptr);
		target->runAction(seq);
	}
}
