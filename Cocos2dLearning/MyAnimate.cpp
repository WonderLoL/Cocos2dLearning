#include "MyAnimate.h"
Scene* MyAnimate::createScene()
{
	Scene* scene = Scene::create();
	auto layer = MyAnimate::create();
	scene->addChild(layer);
	return scene;
}

bool MyAnimate::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visiblesize = Director::getInstance()->getVisibleSize();
	//hello->setAnchorPoint(Vec2(0, 0));
	//hello->setPositionY(visiblesize.height / 2);            //���õ������ƶ�����Ϸ����
    //this->addChild(hello);           //һ��Ҫ��init���潫hello��add��ȥ����
	//��������SpriteͼƬ��������Ļ������
	//auto playSprite = Sprite::create("player.jpg");
	//playSprite->setPosition(50,50);
	//GameMove(playSprite);            //��Ϸ�����ƶ�
	//GameScale(playSprite);           //��Ϸ��������
	//GameRotate(playSprite);          //��Ϸ������ת
	//GameFade(playSprite);            //��Ϸ���嵭�뵭��
	//GameBlink(playSprite);           //��Ϸ������˸
	//GameSequence(playSprite);        //�������ж���
	//GameSpawn(playSprite);           //����ͬ������
	//CreateFrameAnimate();            //����֡����  
	//CreateSpineAnimate();            //����spine����
	//CreateTexturePackerAnimate();    //����TexturePackerͼƬ���������Ķ���
	//scheduleUpdate();                //Ĭ�ϵ�������ʹ��,��ÿһ֡����һ��
	//schedule(schedule_selector(MyAnimate::MyUpdate), 1, kRepeatForever, 3);   //pramas:1.��Ҫ���õĺ��� 2.����ʱ����  3.����һ�κ󻹻ᴥ���Ĵ���  4.��һ�δ���֮ǰ���ӳ�
	//scheduleOnce(schedule_selector(MyAnimate::UpdateOnce),5.0f);                //pramas:1.��Ҫ�����õĺ���  2.�ӳٵ�ʱ��


	/*this->addChild(playSprite);*/

	return true;
}

//��Ϸ�����ƶ��Ĵ���  MoveTo��MoveBy  (float time,Vec2)   ����������ͬʱ����,λ�Ʋ������������������
void MyAnimate::GameMove(Sprite* playSprite)
{
	MoveTo* moveTo = MoveTo::create(2.0f, Point(visiblesize.width / 2, visiblesize.height / 2));
	MoveBy* moveBy = MoveBy::create(2.0f, Point(500, 0));
	playSprite->runAction(moveTo);
	playSprite->runAction(moveBy);
}

//��Ϸ����ߴ����ŵĴ���   ScaleTo��ScaleBy  (float time,float index,float index)  ������ͬʱ����ʱ˭������ں���˭Ϊ׼
void MyAnimate::GameScale(Sprite* playSprite)
{
	ScaleTo* scaleTo = ScaleTo::create(2.0f, 5.0f, 5.0f);
	ScaleBy* scaleBy = ScaleBy::create(2.0f, 3.0f, 3.0f);
	playSprite->runAction(scaleTo);
	playSprite->runAction(scaleBy);
}

//��Ϸ���嵭�뵭���Ĵ��� FadeIn(����)   FadeOut(����)   FadeTo(��ɫ��ĳ�̶ֳ�)   ��ʱ�䳤��Ϊ����ͬһʱ��˭������ں���˭Ϊ׼
void MyAnimate::GameFade(Sprite* playSprite)
{
	auto FadeOutAnimate = FadeOut::create(10.0f);
	auto FadeInAnimate = FadeIn::create(5.0);
	auto FadeToAnimate = FadeTo::create(2.0f, 30);
	//playSprite->runAction(FadeOutAnimate);
	//playSprite->runAction(FadeToAnimate);
	playSprite->setOpacity(40);
	playSprite->runAction(FadeInAnimate);
}

//��Ϸ������ת�Ĵ���  RotateTo��RotateBy ��float time, float angel��  ˳ʱ����� ������ͬʱ����ʱ˭������ں�˭Ϊ׼
void MyAnimate::GameRotate(Sprite* playSprite)
{
	RotateTo* rotateTo = RotateTo::create(2.0f, 150.0f);
	RotateBy* rotateBy = RotateBy::create(2.0f, 90.0f);
	
	playSprite->runAction(rotateBy);
	playSprite->runAction(rotateTo);
}

//��Ϸ������˸�Ĵ���
void MyAnimate::GameBlink(Sprite* playSprite)
{
	auto blinkAnimate = Blink::create(3.0f, 5);
	playSprite->runAction(blinkAnimate);
}

//��Ϸ��������ж���   ����һ����˳����в��ŵ�
void MyAnimate::GameSequence(Sprite* playSprite)
{
	auto moveTo = MoveTo::create(2.0f, Point(visiblesize.width / 2, visiblesize.height / 2));
	auto roateTo = RotateTo::create(2.0f, 90.0f);
	auto scaleTo = ScaleTo::create(2.0f, 2);
	auto fadeOut = FadeOut::create(2.0f);
	auto mySequence = Sequence::create(moveTo, roateTo, scaleTo, fadeOut,nullptr);
	playSprite->runAction(mySequence);
	//playSprite->runAction(mySequence->reverse());   //������ת�޷��������У� ��Ϊnullptr?
}

//��Ϸ�������Spawn������ͬʱ��ɶ�����ִ��
void MyAnimate::GameSpawn(Sprite* playSprite)
{
	auto moveTo = MoveTo::create(2.0f, Point(visiblesize.width / 2, visiblesize.height / 2));
	auto roateTo = RotateTo::create(2.0f, 90.0f);
	auto scaleTo = ScaleTo::create(2.0f, 2);
	auto fadeOut = FadeOut::create(5.0f);
	auto mySpawn = Spawn::create(moveTo, roateTo, scaleTo, fadeOut, nullptr);
	playSprite->runAction(mySpawn);
}

//��������֡����  
void MyAnimate::CreateFrameAnimate()
{
	auto TrumpRunTexture =TextureCache::getInstance()->addImage("trumprun.png");
	Vector<SpriteFrame* > TrumpFrames(24);
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 6; row++)
		{
			auto frame = SpriteFrame::createWithTexture(TrumpRunTexture, Rect(47 * row, 47 * col, 47, 47));   //ע�����سߴ�Ĵ�С
			TrumpFrames.pushBack(frame);
		}

	}
	auto play =Sprite::create();
	play->setPosition(visiblesize.width/2,visiblesize.height/2);
	Animation* animation = Animation::createWithSpriteFrames(TrumpFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	play->runAction(RepeatForever::create(animate));
	CCLOG("run it");
	this->addChild(play,1);
}

//����TexutrePacker�����ͼ��.plist�ļ���������Ӧ�Ķ���
void MyAnimate::CreateTexturePackerAnimate()
{
	 SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Texture/Packer.plist");  //��ͼƬ�ļ��ϴ���SpriteFrame�Ĺ�����������
	/* SpriteFrameCache* pCache = SpriteFrameCache::getInstance();*/
	 //pCache->addSpriteFramesWithFile("Texture/Packer.plist");
	 Vector<SpriteFrame* > CheerDance(8);                                                          //�����������洢����֡
	 char name[15];
	 for (int i = 0; i < 8; i++)                                                                   //��ͼƬ�����еľ���֡ͼƬ �ֲ������������
	 {
		 sprintf(name, "banana%d.gif", i);
		 SpriteFrame* frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
		 //auto frame = pCache->spriteFrameByName(name);
		 CheerDance.pushBack(frame);
	 }

	 auto player = Sprite::create();
	 player->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	 Animation* cheerAnimation = Animation::createWithSpriteFrames(CheerDance,0.2f);   //ͨ������֡������������
	 Animate* cheerAnimate = Animate::create(cheerAnimation);
	 player->runAction(RepeatForever::create(cheerAnimate));                     //һֱ���Ŷ���
	 CCLOG("CheerDacning");
	 this->addChild(player, 1);

}


//����Spine��������   
void MyAnimate::CreateSpineAnimate()
{
	auto skeletonNode = SkeletonAnimation::createWithFile("spineboy.json", "boy.atlas", 0.5f);  //����1.0f  ��ʾͼƬ��ѹ������
	skeletonNode->setPosition(Point(300, 300));

	skeletonNode->setMix("walk", "jump", 0.5f);        //���ද�����ϣ����ʱ��Ϊ0.5f  �ںϵ����û����е�㲻��
	skeletonNode->setAnimation(0, "jump", true);
	skeletonNode->setAnimation(0, "walk", true);        //true��ʾѭ�����Ŷ���   ��һ�����������ȼ�����ֵԽ��Խ�Ȳ���   ˭������ں���˭Ϊ׼
	
	skeletonNode->setTimeScale(0.5f);                   //���ö��������ٶ�
	skeletonNode->setDebugBonesEnabled(true);           //�򿪹�������
	this->addChild(skeletonNode);
}

//Ĭ�ϵ�������ʹ��ScheduleUpdate   ����Ҫ���ܹ�OK��������init�����н�hello��add�����в���
void MyAnimate::update(float dt)
{
	if (transition < visiblesize.width)
	{
		transition += 1;
		hello->setPositionX(transition);
		CCLOG("update");
	}
}

//�Զ��������   ��Ҫ����ʱ���ȵĺ���
void MyAnimate::MyUpdate(float dt)
{
	CCLOG("Myupdate");
}

//���ε�����    ֻ�ᱻ����һ��
void MyAnimate::UpdateOnce(float dt)
{
	CCLOG("UpdateOnce");
}