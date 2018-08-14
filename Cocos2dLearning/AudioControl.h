#ifndef _AudioControl_H_
#define _AudioControl_H_
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "ui\CocosGUI.h" <span style="white-space:pre">
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d;
using namespace ui;

class AudioControl:public Layer
{
public:
	AudioControl();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AudioControl);
	void CurrentLabel();
	void MenuItem();
	virtual void onEnter();
	virtual void onExit();
private:
	SimpleAudioEngine* myAudioEngine;
	int audioId;
	bool isLoop;
	Size visibleSize;
};
#endif
