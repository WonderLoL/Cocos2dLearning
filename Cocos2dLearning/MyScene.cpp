#include "MyScene.h"
#include "SecondScene.h"
Scene* MyScene::createScene()
{
	//����һ������������
	auto scene = Scene::create();

	//����һ��MyScene����(��),������Layer����ķ���
	auto layer = MyScene::create();    

	//��MyScene������ӵ�������
	scene->addChild(layer);

	return scene;
 }

bool MyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//��ȡ��Ϸ����Ļ�ĳߴ�
	auto visiblesize = Director::getInstance()->getVisibleSize();

	//�������飬�����������鶨����λ�ã���С���Լ�ǰ��˳��   ����ͼ������SetScale
	auto spriteBG = Sprite::create("BG.jpg");
	spriteBG->setPosition(Vec2(visiblesize.width/2,visiblesize.height/2));
	float scale_x = visiblesize.width / (float)500;
	float scale_y = visiblesize.height / (float)313;
	spriteBG->setContentSize(Size(visiblesize.width, visiblesize.height));
	/*spriteBG->setScale(3.0, 3.0);*/     //�޷��޸�ͼƬ�Ĵ�С
	this->addChild(spriteBG);

	//auto sprite1 = Sprite::create("san.jpg");
	//sprite1->setPosition(Vec2(visiblesize.width / 2, visiblesize.height / 2));
	//sprite1->setScaleY(0.5);
	//this->addChild(sprite1,1);

	//auto sprite2 = Sprite::create("HelloWorld.png");
	//sprite2->setPosition(Vec2(visiblesize.width / 2, visiblesize.height / 2));
	//sprite2->setScale(0.5, 0.5);
	//this->addChild(sprite2, 2);


	//����ͼƬ�˵���,����CC_CALLBACK_1��һ��bind���������а󶨵ĺ������ͱ����ǹ̶���
	auto logBtnMenuItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		                                        CC_CALLBACK_1(MyScene::ImagePrint, this));
	logBtnMenuItem->setScale(5.0, 5.0);
	
	//������ǩlabel,Ȼ���øñ�ǩȥ������ǩ�˵���
	auto label = Label::create("I am LabelItem","Arial", 30);
	label->setTextColor(Color4B::RED);
	auto labelMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(MyScene::LabelPrint, this));
	labelMenuItem->setContentSize(Size(200, 100));

	//����һ���ı��˵���
	auto fontStr = "I am FontItem";
	auto fontMenuItem = MenuItemFont::create(fontStr,CC_CALLBACK_1(MyScene::FontPrint, this));
	fontMenuItem->setColor(Color3B::GREEN);
	fontMenuItem->setContentSize(Size(200, 100));

	//�����˵���
	auto MyMenu = Menu::create(logBtnMenuItem, labelMenuItem, fontMenuItem,NULL);
	MyMenu->setPosition(visiblesize.width / 2, visiblesize.height / 2);  //���õ���Ļ���м�
	this->addChild(MyMenu, 1);
	MyMenu->alignItemsVerticallyWithPadding(30);
	CCLOG("%f", visiblesize.width / 2);
	CCLOG("%f", visiblesize.height / 2);
	return true;
}

void MyScene::ImagePrint(Ref* psender)
{
	CCLOG("Change to the SecondScene");
	CCDirector::sharedDirector()->replaceScene(TransitionMoveInR::create(2,SecondScene::createScene()));

}

void MyScene::LabelPrint(Ref* psender)
{
	CCLOG("%s", "I am LabelItem");
}

void MyScene::FontPrint(Ref* psender)
{
	CCLOG("%s", "I am FontItem");
}


