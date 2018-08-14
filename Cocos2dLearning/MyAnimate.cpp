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
	//hello->setPositionY(visiblesize.height / 2);            //利用调度器移动的游戏物体
    //this->addChild(hello);           //一定要在init里面将hello给add进去才行
	//将创建的Sprite图片放置在屏幕的中央
	//auto playSprite = Sprite::create("player.jpg");
	//playSprite->setPosition(50,50);
	//GameMove(playSprite);            //游戏物体移动
	//GameScale(playSprite);           //游戏物体缩放
	//GameRotate(playSprite);          //游戏物体旋转
	//GameFade(playSprite);            //游戏物体淡入淡出
	//GameBlink(playSprite);           //游戏物体闪烁
	//GameSequence(playSprite);        //播放序列动画
	//GameSpawn(playSprite);           //播放同步动画
	//CreateFrameAnimate();            //播放帧动画  
	//CreateSpineAnimate();            //播放spine动画
	//CreateTexturePackerAnimate();    //播放TexturePacker图片集所制作的动画
	//scheduleUpdate();                //默认调度器的使用,会每一帧调用一次
	//schedule(schedule_selector(MyAnimate::MyUpdate), 1, kRepeatForever, 3);   //pramas:1.需要调用的函数 2.触发时间间隔  3.触发一次后还会触发的次数  4.第一次触发之前的延迟
	//scheduleOnce(schedule_selector(MyAnimate::UpdateOnce),5.0f);                //pramas:1.需要被调用的函数  2.延迟的时间


	/*this->addChild(playSprite);*/

	return true;
}

//游戏物体移动的代码  MoveTo和MoveBy  (float time,Vec2)   两个动作会同时进行,位移操作两个坐标量会叠加
void MyAnimate::GameMove(Sprite* playSprite)
{
	MoveTo* moveTo = MoveTo::create(2.0f, Point(visiblesize.width / 2, visiblesize.height / 2));
	MoveBy* moveBy = MoveBy::create(2.0f, Point(500, 0));
	playSprite->runAction(moveTo);
	playSprite->runAction(moveBy);
}

//游戏物体尺寸缩放的代码   ScaleTo和ScaleBy  (float time,float index,float index)  两个都同时存在时谁的语句在后以谁为准
void MyAnimate::GameScale(Sprite* playSprite)
{
	ScaleTo* scaleTo = ScaleTo::create(2.0f, 5.0f, 5.0f);
	ScaleBy* scaleBy = ScaleBy::create(2.0f, 3.0f, 3.0f);
	playSprite->runAction(scaleTo);
	playSprite->runAction(scaleBy);
}

//游戏物体淡入淡出的代码 FadeIn(淡入)   FadeOut(淡出)   FadeTo(颜色到某种程度)   以时间长的为主，同一时间谁的语句在后以谁为准
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

//游戏物体旋转的代码  RotateTo和RotateBy （float time, float angel）  顺时针操作 两个都同时存在时谁的语句在后谁为准
void MyAnimate::GameRotate(Sprite* playSprite)
{
	RotateTo* rotateTo = RotateTo::create(2.0f, 150.0f);
	RotateBy* rotateBy = RotateBy::create(2.0f, 90.0f);
	
	playSprite->runAction(rotateBy);
	playSprite->runAction(rotateTo);
}

//游戏物体闪烁的代码
void MyAnimate::GameBlink(Sprite* playSprite)
{
	auto blinkAnimate = Blink::create(3.0f, 5);
	playSprite->runAction(blinkAnimate);
}

//游戏物体的序列动画   按照一定的顺序进行播放的
void MyAnimate::GameSequence(Sprite* playSprite)
{
	auto moveTo = MoveTo::create(2.0f, Point(visiblesize.width / 2, visiblesize.height / 2));
	auto roateTo = RotateTo::create(2.0f, 90.0f);
	auto scaleTo = ScaleTo::create(2.0f, 2);
	auto fadeOut = FadeOut::create(2.0f);
	auto mySequence = Sequence::create(moveTo, roateTo, scaleTo, fadeOut,nullptr);
	playSprite->runAction(mySequence);
	//playSprite->runAction(mySequence->reverse());   //动作反转无法正常进行？ 因为nullptr?
}

//游戏物体添加Spawn动画，同时完成动画的执行
void MyAnimate::GameSpawn(Sprite* playSprite)
{
	auto moveTo = MoveTo::create(2.0f, Point(visiblesize.width / 2, visiblesize.height / 2));
	auto roateTo = RotateTo::create(2.0f, 90.0f);
	auto scaleTo = ScaleTo::create(2.0f, 2);
	auto fadeOut = FadeOut::create(5.0f);
	auto mySpawn = Spawn::create(moveTo, roateTo, scaleTo, fadeOut, nullptr);
	playSprite->runAction(mySpawn);
}

//创建序列帧动画  
void MyAnimate::CreateFrameAnimate()
{
	auto TrumpRunTexture =TextureCache::getInstance()->addImage("trumprun.png");
	Vector<SpriteFrame* > TrumpFrames(24);
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 6; row++)
		{
			auto frame = SpriteFrame::createWithTexture(TrumpRunTexture, Rect(47 * row, 47 * col, 47, 47));   //注意像素尺寸的大小
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

//利用TexutrePacker打包的图集.plist文件来创建相应的动画
void MyAnimate::CreateTexturePackerAnimate()
{
	 SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Texture/Packer.plist");  //将图片的集合存入SpriteFrame的共享缓冲区当中
	/* SpriteFrameCache* pCache = SpriteFrameCache::getInstance();*/
	 //pCache->addSpriteFramesWithFile("Texture/Packer.plist");
	 Vector<SpriteFrame* > CheerDance(8);                                                          //创建容器，存储精灵帧
	 char name[15];
	 for (int i = 0; i < 8; i++)                                                                   //将图片集合中的精灵帧图片 分拆存入容器当中
	 {
		 sprintf(name, "banana%d.gif", i);
		 SpriteFrame* frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
		 //auto frame = pCache->spriteFrameByName(name);
		 CheerDance.pushBack(frame);
	 }

	 auto player = Sprite::create();
	 player->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	 Animation* cheerAnimation = Animation::createWithSpriteFrames(CheerDance,0.2f);   //通过精灵帧容器创建动画
	 Animate* cheerAnimate = Animate::create(cheerAnimation);
	 player->runAction(RepeatForever::create(cheerAnimate));                     //一直播放动画
	 CCLOG("CheerDacning");
	 this->addChild(player, 1);

}


//播放Spine骨骼动画   
void MyAnimate::CreateSpineAnimate()
{
	auto skeletonNode = SkeletonAnimation::createWithFile("spineboy.json", "boy.atlas", 0.5f);  //其中1.0f  表示图片的压缩倍数
	skeletonNode->setPosition(Point(300, 300));

	skeletonNode->setMix("walk", "jump", 0.5f);        //两类动画相混合，混合时间为0.5f  融合的作用还是有点搞不懂
	skeletonNode->setAnimation(0, "jump", true);
	skeletonNode->setAnimation(0, "walk", true);        //true表示循环播放动画   第一个参数是优先级，数值越高越先播放   谁的语句在后以谁为准
	
	skeletonNode->setTimeScale(0.5f);                   //设置动画播放速度
	skeletonNode->setDebugBonesEnabled(true);           //打开骨骼调试
	this->addChild(skeletonNode);
}

//默认调度器的使用ScheduleUpdate   其中要想能够OK，必须在init函数中将hello给add到层中才行
void MyAnimate::update(float dt)
{
	if (transition < visiblesize.width)
	{
		transition += 1;
		hello->setPositionX(transition);
		CCLOG("update");
	}
}

//自定义调度器   需要被定时调度的函数
void MyAnimate::MyUpdate(float dt)
{
	CCLOG("Myupdate");
}

//单次调度器    只会被调用一次
void MyAnimate::UpdateOnce(float dt)
{
	CCLOG("UpdateOnce");
}