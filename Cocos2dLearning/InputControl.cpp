#include "InputControl.h"
Scene* InputControl::createScene()
{
	auto scene = Scene::create();
	auto layer = InputControl::create();
	scene->addChild(layer);
	return scene;
}

bool InputControl::init()
{
	if (!Layer::init())
	{
		return false;
	}
	mySprite = Sprite::create("HelloWorld.png");
	mySprite->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	this->addChild(mySprite);
	RigisterEvent();                                  //注册各类触发事件
	scheduleUpdate();                                 //利用update帧函数来完成按键持续按下的信息监测
	//auto myKeyListener1 = EventListenerKeyboard::create();
	//myKeyListener1->onKeyPressed = CC_CALLBACK_2(InputControl::OnKeyPressedHandle, this);  //给键盘监听器绑定回调函数  ，类似与观察者模式主题订阅
	//_eventDispatcher->addEventListenerWithFixedPriority(myKeyListener1, this);
	return true;
}


//创建事件分发器，以及键盘、鼠标的监听器，给各监听器注册上相应的回调函数
void InputControl::RigisterEvent()
{
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();    //创建一个事件分发器

	auto myKeyListener = EventListenerKeyboard::create();    //创建一个键盘监听器
	myKeyListener->onKeyPressed = CC_CALLBACK_2(InputControl::OnKeyPressedHandle, this);  //给键盘监听器绑定回调函数  ，类似与观察者模式主题订阅
	myKeyListener->onKeyReleased = CC_CALLBACK_2(InputControl::OnKeyReleaseHandle, this);

	auto myMouseListener = EventListenerMouse::create();     //创建一个鼠标监听器，监听器中有很多种主题
	myMouseListener->onMouseMove = CC_CALLBACK_1(InputControl::MouseMoveEventHandle, this);
	myMouseListener->onMouseDown = CC_CALLBACK_1(InputControl::MouseDownHandle, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);   //事件分发器注册监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);
}


//给键盘按键监听器绑定相应的回调函数，能够持续监测按键是否按下  类似与观察者模式，其中键盘监听器是主题，回调函数是订阅者
void InputControl::OnKeyPressedHandle(EventKeyboard::KeyCode keycode, Event *e)
{

	auto moveUp = MoveBy::create(0.1f, Point(0, 20.0f));     //相应的动作
	auto moveDown = MoveBy::create(0.1f, Point(0, -20.0f));
	auto moveLeft = MoveBy::create(0.1f, Point(-20.0f, 0));
	auto moveRight = MoveBy::create(0.1f, Point(20.0f, 0));
	switch (keycode)                                         //判断按下的键值，从而处理相应的函数
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		/*mySprite->runAction(moveUp);*/
		IsUp = true;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		/*mySprite->runAction(moveDown);*/
		IsDown = true;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		//mySprite->runAction(moveLeft);
		IsLeft = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		//mySprite->runAction(moveRight);
		IsRight = true;
		break;
	default:
		break;
	}
}

//定义按键松开事件的回调函数
void InputControl::OnKeyReleaseHandle(EventKeyboard::KeyCode keycode, Event *e)
{
	switch (keycode)                                         //判断按下的键值，从而处理相应的函数
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		IsUp = false;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		IsDown = false;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		IsLeft = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		IsRight = false;
		break;
	default:
		break;
	}
}

//处理鼠标事件的回调函数  本质就是观察者模式
void InputControl::MouseMoveEventHandle(Event *event)
{
	if (MouseIsTrigger)
	{
		EventMouse* e = (EventMouse*)event;
		PosX = e->getCursorX();
		PosY = e->getCursorY();
		mySprite->setPosition(PosX, PosY);
	}
}

//通过鼠标的按键来处理是 鼠标操控还是键盘操控 ，鼠标点击来完成操控的切换
void InputControl::MouseDownHandle(Event *event)
{
	MouseIsTrigger = !MouseIsTrigger;
}

//进行持续按键移动的动作处理
void InputControl::update(float dt)
{
	if (MouseIsTrigger)
	{
		return;
	}
	if (IsUp)
	{
		PosY += 2.0f;
	}
	else if (IsDown)
	{
		PosY -= 2.0f;
	}
	if (IsLeft)
	{
		PosX -= 2.0f;
	}
	else if (IsRight)
	{
		PosX += 2.0f;
	}
	if (!MouseIsTrigger)
	{
		mySprite->setPosition(PosX, PosY);
	}
}