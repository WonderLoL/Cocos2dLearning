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

//��һ��SimpleAudioEngine�Ĳ��Ա�ǩ
void AudioControl::CurrentLabel()
{
	auto simpleAudioLabel = Label::createWithSystemFont("SimpleEngineAudio Test", "", 30);            //����̧ͷ��ǩ  �ڶ���������
	simpleAudioLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - simpleAudioLabel->getContentSize().height));
	addChild(simpleAudioLabel);
}

//������һ�����԰�����Menu�˵������ְ�������
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
		Director::getInstance()->replaceScene(InputControl::createScene());             //�л��ڶ���Audio����
	});
	enterNextAudioItem->setPosition(Vec2(0, -visibleSize.height / 4));

	auto simpleAudioMenu = Menu::create(playItem, stopItem, pauseItem, resumeItem, enterNextAudioItem,nullptr);     
	simpleAudioMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(simpleAudioMenu,1);
	int i = 1;
}

//�������ʼ��
void AudioControl::onEnter()
{
	Layer::onEnter();
	myAudioEngine->preloadEffect("music/background.mp3");    //Ԥ������Ч
	CCLOG("onEnter......");
}

//�˳�������ʱ�����Ҫ ɾ�������е���Ч
void AudioControl::onExit()
{
	if (myAudioEngine)
	{
		myAudioEngine->unloadEffect("music/background.mp3");
	}
	Layer::onExit();
}