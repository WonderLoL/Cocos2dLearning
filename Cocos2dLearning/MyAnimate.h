#ifndef _MyAnimate_H_
#define _MyAnimate_H_
#include "cocos2d.h"
#include<vector>
#include<stdio.h>
#include "spine\spine-cocos2dx.h"
using namespace spine;
using namespace cocos2d;
USING_NS_CC;
using namespace std;


class MyAnimate:public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MyAnimate);
	
private:
	Sprite* hello = Sprite::create("HelloWorld.png");
	float transition = 0;
	Size visiblesize;
	void GameMove(Sprite* playSprite);
	void GameScale(Sprite* playSprite);
	void GameRotate(Sprite* playSprite);
	void GameFade(Sprite* playSprite);
	void GameBlink(Sprite* playSprite);
	void GameSequence(Sprite* playSprite);
	void GameSpawn(Sprite* playSprite);
	void CreateFrameAnimate();
	void CreateTexturePackerAnimate();
	void CreateSpineAnimate();
	void update(float dt) override;
	void MyUpdate(float dt);
	void UpdateOnce(float dt);
};
#endif // _MyAnimate_H_
