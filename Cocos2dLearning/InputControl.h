#ifndef _InputControl_H_
#define _InputControl_H_
#include "cocos2d.h"
using namespace cocos2d;

class InputControl:public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(InputControl);
private:
	bool IsUp = false;
	bool IsDown = false;
	bool IsLeft = false;
	bool IsRight = false;
	bool MouseIsTrigger = false;
	float PosX=1024/2;
	float PosY=768/2;
	
	Sprite* mySprite;

	Size visiblesize = Director::getInstance()->getVisibleSize();
	void OnKeyPressedHandle(EventKeyboard::KeyCode keycode, Event *e);
	void OnKeyReleaseHandle(EventKeyboard::KeyCode keycode, Event *e);
	void MouseMoveEventHandle(Event *event);
	void MouseDownHandle(Event *event);
	void RigisterEvent();
	void update(float dt) override;


};

#endif 


