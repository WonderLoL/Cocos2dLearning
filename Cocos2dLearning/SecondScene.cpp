#include "SecondScene.h"
#include "MyScene.h"
//切换过程中一定要包含相应的头文件
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
	//创建背景层
	auto spriteBG = Sprite::create("rule.jpg");
	spriteBG->setPosition(visiblesize.width/2, visiblesize.height/2);
	spriteBG->setContentSize(Size(visiblesize.width, visiblesize.height));
	this->addChild(spriteBG,0);

	//创建MenuItemImage 并且绑定切换场景的函数
	auto ChangeScene = MenuItemImage::create("CloseNormal.png", "CloseSelected",
		                                     CC_CALLBACK_1(SecondScene::ChangeScene, this));
	/*ChangeScene->setContentSize(Size(300, 300));*/
	ChangeScene->setScale(5, 5);
	auto SecondMenu = Menu::create(ChangeScene, NULL);
	SecondMenu->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	this->addChild(SecondMenu, 1);
	return true;
}

//切换场景的回调函数
void SecondScene::ChangeScene(Ref* psender)
{
	CCLOG("Change to the MyScene");
	CCDirector::sharedDirector()->replaceScene(TransitionCrossFade::create(2, MyScene::createScene()));  //不同的函数表示不同的切换方式
}