#include "MyScene.h"
#include "SecondScene.h"
Scene* MyScene::createScene()
{
	//创建一个场景对形象
	auto scene = Scene::create();

	//创建一个MyScene对象(层),调用了Layer基类的方法
	auto layer = MyScene::create();    

	//将MyScene对象添加到场景中
	scene->addChild(layer);

	return scene;
 }

bool MyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//获取游戏中屏幕的尺寸
	auto visiblesize = Director::getInstance()->getVisibleSize();

	//创建精灵，并给各个精灵定义了位置，大小，以及前后顺序   背景图好像不能SetScale
	auto spriteBG = Sprite::create("BG.jpg");
	spriteBG->setPosition(Vec2(visiblesize.width/2,visiblesize.height/2));
	float scale_x = visiblesize.width / (float)500;
	float scale_y = visiblesize.height / (float)313;
	spriteBG->setContentSize(Size(visiblesize.width, visiblesize.height));
	/*spriteBG->setScale(3.0, 3.0);*/     //无法修改图片的大小
	this->addChild(spriteBG);

	//auto sprite1 = Sprite::create("san.jpg");
	//sprite1->setPosition(Vec2(visiblesize.width / 2, visiblesize.height / 2));
	//sprite1->setScaleY(0.5);
	//this->addChild(sprite1,1);

	//auto sprite2 = Sprite::create("HelloWorld.png");
	//sprite2->setPosition(Vec2(visiblesize.width / 2, visiblesize.height / 2));
	//sprite2->setScale(0.5, 0.5);
	//this->addChild(sprite2, 2);


	//创建图片菜单项,其中CC_CALLBACK_1是一个bind函数，其中绑定的函数类型必须是固定的
	auto logBtnMenuItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		                                        CC_CALLBACK_1(MyScene::ImagePrint, this));
	logBtnMenuItem->setScale(5.0, 5.0);
	
	//创建标签label,然后用该标签去创建标签菜单项
	auto label = Label::create("I am LabelItem","Arial", 30);
	label->setTextColor(Color4B::RED);
	auto labelMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(MyScene::LabelPrint, this));
	labelMenuItem->setContentSize(Size(200, 100));

	//创建一个文本菜单项
	auto fontStr = "I am FontItem";
	auto fontMenuItem = MenuItemFont::create(fontStr,CC_CALLBACK_1(MyScene::FontPrint, this));
	fontMenuItem->setColor(Color3B::GREEN);
	fontMenuItem->setContentSize(Size(200, 100));

	//创建菜单项
	auto MyMenu = Menu::create(logBtnMenuItem, labelMenuItem, fontMenuItem,NULL);
	MyMenu->setPosition(visiblesize.width / 2, visiblesize.height / 2);  //设置到屏幕的中间
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


