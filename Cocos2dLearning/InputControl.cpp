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
	RigisterEvent();                                  //ע����ഥ���¼�
	scheduleUpdate();                                 //����update֡��������ɰ����������µ���Ϣ���
	//auto myKeyListener1 = EventListenerKeyboard::create();
	//myKeyListener1->onKeyPressed = CC_CALLBACK_2(InputControl::OnKeyPressedHandle, this);  //�����̼������󶨻ص�����  ��������۲���ģʽ���ⶩ��
	//_eventDispatcher->addEventListenerWithFixedPriority(myKeyListener1, this);
	return true;
}


//�����¼��ַ������Լ����̡����ļ�����������������ע������Ӧ�Ļص�����
void InputControl::RigisterEvent()
{
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();    //����һ���¼��ַ���

	auto myKeyListener = EventListenerKeyboard::create();    //����һ�����̼�����
	myKeyListener->onKeyPressed = CC_CALLBACK_2(InputControl::OnKeyPressedHandle, this);  //�����̼������󶨻ص�����  ��������۲���ģʽ���ⶩ��
	myKeyListener->onKeyReleased = CC_CALLBACK_2(InputControl::OnKeyReleaseHandle, this);

	auto myMouseListener = EventListenerMouse::create();     //����һ���������������������кܶ�������
	myMouseListener->onMouseMove = CC_CALLBACK_1(InputControl::MouseMoveEventHandle, this);
	myMouseListener->onMouseDown = CC_CALLBACK_1(InputControl::MouseDownHandle, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);   //�¼��ַ���ע�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);
}


//�����̰�������������Ӧ�Ļص��������ܹ�������ⰴ���Ƿ���  ������۲���ģʽ�����м��̼����������⣬�ص������Ƕ�����
void InputControl::OnKeyPressedHandle(EventKeyboard::KeyCode keycode, Event *e)
{

	auto moveUp = MoveBy::create(0.1f, Point(0, 20.0f));     //��Ӧ�Ķ���
	auto moveDown = MoveBy::create(0.1f, Point(0, -20.0f));
	auto moveLeft = MoveBy::create(0.1f, Point(-20.0f, 0));
	auto moveRight = MoveBy::create(0.1f, Point(20.0f, 0));
	switch (keycode)                                         //�жϰ��µļ�ֵ���Ӷ�������Ӧ�ĺ���
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

//���尴���ɿ��¼��Ļص�����
void InputControl::OnKeyReleaseHandle(EventKeyboard::KeyCode keycode, Event *e)
{
	switch (keycode)                                         //�жϰ��µļ�ֵ���Ӷ�������Ӧ�ĺ���
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

//��������¼��Ļص�����  ���ʾ��ǹ۲���ģʽ
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

//ͨ�����İ����������� ���ٿػ��Ǽ��̲ٿ� �����������ɲٿص��л�
void InputControl::MouseDownHandle(Event *event)
{
	MouseIsTrigger = !MouseIsTrigger;
}

//���г��������ƶ��Ķ�������
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