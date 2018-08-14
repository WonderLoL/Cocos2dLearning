#include "AudioControl.h"
#include "MyPhysicWorld.h"
#include "InputControl.h"

AudioControl::AudioControl()
{
	myAudioEngine = SimpleAudioEngine::getInstance();
	audioId = 0;
	isLoop = true;
	visibleSize = Director::getInstance()->getVisibleSize();
}

Scene* AudioControl::createScene()
{
	Scene* scene = Scene::create();
	auto layer = AudioControl::create();
	scene->addChild(layer);
	return scene;
}

bool AudioControl::init()
{
	if (!Layer::init())
	{
		return false;
	}
	CurrentLabel();
	MenuItem();
}

//第一个SimpleAudioEngine的测试标签
void AudioControl::CurrentLabel()
{
	auto simpleAudioLabel = Label::createWithSystemFont("SimpleEngineAudio Test", "", 30);            //创建抬头标签  第二个参数？
	simpleAudioLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - simpleAudioLabel->getContentSize().height));
	addChild(simpleAudioLabel);
}

//创建第一个测试案例的Menu菜单，各种按键控制
void AudioControl::MenuItem()
{
	auto playItem = MenuItemFont::create("Play Music", [&](Ref* sender) 
	{
		audioId =myAudioEngine->playEffect("music/LuckyDay.mp3",isLoop);
	});
	playItem->setPosition(Vec2(-visibleSize.width / 4, visibleSize.height / 4));

	auto stopItem = MenuItemFont::create("Stop Music", [&](Ref* sender) 
	{
		if (audioId != 0)
		{
			myAudioEngine->stopEffect(audioId);
			audioId = 0;
		}
	});
	stopItem->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 4));

	auto pauseItem = MenuItemFont::create("Pause Music", [&](Ref* sender)
	{
		if (audioId != 0)
		{
			myAudioEngine->stopEffect(audioId);
		}
	});
	pauseItem->setPosition(Vec2(Vec2(-visibleSize.width / 4, 0)));

	auto resumeItem = MenuItemFont::create("Resume Music", [&](Ref* sender) 
	{
		if (audioId != 0)
		{
			myAudioEngine->resumeEffect(audioId);
		}
	});
	resumeItem->setPosition(Vec2(visibleSize.width / 4, 0));

	auto enterNextAudioItem = MenuItemFont::create("Click Here to Change The Scene", [&](Ref* sender) 
	{
		Director::getInstance()->replaceScene(InputControl::createScene());             //切换第二个Audio场景
	});
	enterNextAudioItem->setPosition(Vec2(0, -visibleSize.height / 4));

	auto simpleAudioMenu = Menu::create(playItem, stopItem, pauseItem, resumeItem, enterNextAudioItem,nullptr);     
	simpleAudioMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(simpleAudioMenu,1);
	int i = 1;
}

//类似与初始化
void AudioControl::onEnter()
{
	Layer::onEnter();
	myAudioEngine->preloadEffect("music/background.mp3");    //预加载音效
	CCLOG("onEnter......");
}

//退出这个类的时候必须要 删除缓存中的音效
void AudioControl::onExit()
{
	if (myAudioEngine)
	{
		myAudioEngine->unloadEffect("music/background.mp3");
	}
	Layer::onExit();
}