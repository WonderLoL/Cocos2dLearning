#include "SecondScene.h"
#include "MyScene.h"
//�л�������һ��Ҫ������Ӧ��ͷ�ļ�
Scene* SecondScene::createScene()
{
	auto sence = Scene::create();
	auto layer = SecondScene::create();
	sence->addChild(layer);
	return sence;
}

bool SecondScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visiblesize = Director::getInstance()->getVisibleSize();
	//����������
	auto spriteBG = Sprite::create("rule.jpg");
	spriteBG->setPosition(visiblesize.width/2, visiblesize.height/2);
	spriteBG->setContentSize(Size(visiblesize.width, visiblesize.height));
	this->addChild(spriteBG,0);

	//����MenuItemImage ���Ұ��л������ĺ���
	auto ChangeScene = MenuItemImage::create("CloseNormal.png", "CloseSelected",
		                                     CC_CALLBACK_1(SecondScene::ChangeScene, this));
	/*ChangeScene->setContentSize(Size(300, 300));*/
	ChangeScene->setScale(5, 5);
	auto SecondMenu = Menu::create(ChangeScene, NULL);
	SecondMenu->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	this->addChild(SecondMenu, 1);
	return true;
}

//�л������Ļص�����
void SecondScene::ChangeScene(Ref* psender)
{
	CCLOG("Change to the MyScene");
	CCDirector::sharedDirector()->replaceScene(TransitionCrossFade::create(2, MyScene::createScene()));  //��ͬ�ĺ�����ʾ��ͬ���л���ʽ
}