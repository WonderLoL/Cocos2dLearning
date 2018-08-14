#include "MyPhysicWorld.h"
Scene* MyPhysicWorld::createScene()
{
	Scene* scene = Scene::createWithPhysics();
	auto mylayer = MyPhysicWorld::create();
	scene->addChild(mylayer);
	return scene;
}

bool MyPhysicWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//createBgEdgePhysicSprite();
	//initRayCastTestObject();
	touchEvent();
	schedule(schedule_selector(MyPhysicWorld::rayCastRect), 0.2f);
	//schedule(schedule_selector(MyPhysicWorld::rayCastTest), 0.2f);              //查询、射线检测过程中必须利用定时器来完成，否则获取物理世界的过程中会报错
	//shootStone();
	//ballFall();
	//createSteadyPhysicSprite();
	//createDynamicPhysicSprite();

}

//创建一个刚体的边框，让游戏物体无法飞出去
void MyPhysicWorld::createBgEdgePhysicSprite()
{
	auto bgSprite = Sprite::create();
	bgSprite->setPosition(centerPoint);
	auto mapFrame = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);  //创建边框刚体 参数：1.盒子的长宽尺寸   2.材质  3.边框的宽度
	bgSprite->setPhysicsBody(mapFrame);
	this->addChild(bgSprite);
}

//模拟篮球下落的过程
void MyPhysicWorld::ballFall()
{
	auto ballSprite = Sprite::create("ball.png");
	ballSprite->setPosition(centerPoint);
	auto ballPhysicsBody = PhysicsBody::createCircle(ballSprite->getContentSize().width/2,PhysicsMaterial(2.0f,1.5f,0.1f));
	ballPhysicsBody->setGravityEnable(true);
	ballSprite->setPhysicsBody(ballPhysicsBody);
	this->addChild(ballSprite);
}

//发射子弹射击石头,一定要注意配置相应的掩码才能完成碰撞和碰撞检测
void MyPhysicWorld::shootStone()
{
	auto bullet = Sprite::create("HelloWorld.png");
	bullet->setPosition(0, visibleSize.height / 2);
	auto bulletPhysicsBody = PhysicsBody::createBox(bullet->getBoundingBox().size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	bulletPhysicsBody->setGravityEnable(false);
	bulletPhysicsBody->setContactTestBitmask(0x0001);
	bulletPhysicsBody->setVelocity(Vec2(200.0f, 0.0f));
	bulletPhysicsBody->setTag(1);
	//bulletPhysicsBody->applyForce(10*Vec2(1.0f,0));                            //这个力的施加感觉有点问题啊
	bullet->setPhysicsBody(bulletPhysicsBody);
	this->addChild(bullet,1);

	auto stone = Sprite::create("Stone.jpg");
	stone->setPosition(800, visibleSize.height / 2);
	auto stonePhysicsBody = PhysicsBody::createBox(Size(stone->getContentSize().width-350,stone->getContentSize().height-200), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	stonePhysicsBody->setGravityEnable(false);
	stonePhysicsBody->setContactTestBitmask(0x0001);
	stonePhysicsBody->setTag(2);
	stone->setPhysicsBody(stonePhysicsBody);
	this->addChild(stone);

	//给碰撞事件添加监听器
	auto contactListener = EventListenerPhysicsContact::create();   //创建刚体的碰撞的监听器
	contactListener->onContactBegin = CC_CALLBACK_1(MyPhysicWorld::destoryStone,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

//摧毁石头所的回调函数
bool MyPhysicWorld::destoryStone(const PhysicsContact& contact)
{
	auto gameObject1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto gameObject2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
	gameObject1->removeFromParentAndCleanup(true);
	gameObject2->removeFromParentAndCleanup(true);
	return true;
}

//射线检测  游戏物体的初始化 创建了两个带刚体的游戏物体，能够进行射线检测
void MyPhysicWorld::initRayCastTestObject()
{
	rayCastPhysicBody = Sprite::create("HelloWorld.png");
	PhysicsBody* body = PhysicsBody::createBox(rayCastPhysicBody->getContentSize());
	body->setGravityEnable(false);
	rayCastPhysicBody->setPhysicsBody(body);
	rayCastPhysicBody->setPosition(412, 350);
	addChild(rayCastPhysicBody);
	rayCastPhysicBody1 = Sprite::create("HelloWorld.png");
	PhysicsBody* body1 = PhysicsBody::createBox(rayCastPhysicBody->getContentSize());
	body1->setGravityEnable(false);
	rayCastPhysicBody1->setPhysicsBody(body1);
	rayCastPhysicBody1->setPosition(250, 200);
	addChild(rayCastPhysicBody1);
}

//通过触摸事件监听方法实现鼠标点击某个位置 放置一个游戏物体上去
void MyPhysicWorld::touchEvent()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [&](Touch* touch, Event* event)    //Lambda函数
	{
		Vec2 point = touch->getLocation();                           //获取当前鼠标点击时的位置
		auto sprite = Sprite::create("HelloWorld.png");
		auto body = PhysicsBody::createBox(sprite->getContentSize());
		body->setGravityEnable(false);
		sprite->setPhysicsBody(body);
		sprite->setPosition(point);
		this->addChild(sprite);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

//矩阵查询        必须要用定时器来调用，否则获取物理世界的过程中会报错，指针无法获取
void MyPhysicWorld::rayCastRect(float dt)                                     //矩形框物理检测
{
	Scene* scene = (Scene*)getParent();
	PhysicsWorld* world = scene->getPhysicsWorld();                                          
	auto func = [](PhysicsWorld& world, PhysicsShape& shape, void* userData)->bool
	{
		CCLOG("Get it");
		return false;
	};
	world->queryRect(func, Rect(visibleSize.width / 2, visibleSize.height / 2, 300, 300),nullptr);
}

//射线检测方面的函数      每一帧都要检测，调用了相应的定时器
void MyPhysicWorld::rayCastTest(float dt)
{
	Scene* scene = (Scene*)getParent();
	PhysicsWorld* world = scene->getPhysicsWorld();           //获取父物体场景的物理世界引用
	Vec2 d(400 * cosf(angle), 300 * sinf(angle));
	Vec2 endPoint = centerPoint + d;                          //起点是centerPoint    终止点是endPoint
	Vec2 points[5];                                           //用来存储射线检测到的点
	int num = 0;
	auto func = [&points, &num](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)->bool     //Lambda类型的回调函数 有点看不懂
	{
		if (num < 5)
		{
			char a[10];
			sprintf(a, "%d", num);
			CCLOG(a);
			points[num++] = info.contact;
		}
		return true;                  //表示继续扫描接触到的形状点     return false表示不再扫描, 当出现两个接触点的时候会触发两次函数，最近的游戏物体先触发
		//return false;                     //检测到的游戏物体点大于5个就不在继续检测了
	};

	world->rayCast(func, centerPoint, endPoint, nullptr);                    //在当前物理世界中进行射线的检测
	if (drawNode)
	{
		removeChild(drawNode);
	}
	drawNode = DrawNode::create();                                           //创建一个绘图对象
	drawNode->drawSegment(centerPoint, endPoint, 1, Color4F::RED);           //绘制现实的直线
	for (int i = 0; i <num; i++)
	{
		drawNode->drawDot(points[i], 20, Color4F(1.0f, 0, 0, 1));
	}
	addChild(drawNode);
	angle += 5.0f*(float)M_PI / 180.0f;
}

//中间位置添加一个静态的刚体对象
void MyPhysicWorld::createSteadyPhysicSprite()
{
	steadyPhysicBody = Sprite::create("HelloWorld.png");
	auto physicBody = PhysicsBody::createBox(steadyPhysicBody->getBoundingBox().size);     //创建刚体，材质PhysicsMaterial利用了默认材质
	physicBody->setDynamic(false);                          //将刚体设置为静态刚体，不会受到重力等的作用，质量趋于无穷大
	steadyPhysicBody->setPhysicsBody(physicBody);           //给精灵添加了刚体组件
	steadyPhysicBody->setPosition(centerPoint);
	this->addChild(steadyPhysicBody,1);
}

//添加5个动态刚体对中间的静态刚体进行碰撞
void MyPhysicWorld::createDynamicPhysicSprite()
{
	for (int num = 0; num < 5; num++)
	{
		dynamicPhysicBody[num] = Sprite::create("HelloWorld.png");
		auto physicBody = PhysicsBody::createBox(dynamicPhysicBody[num]->getBoundingBox().size,PhysicsMaterial(0.1f,1.0f,0.0f));  //Material三个参数分别为：密度、还原力、摩擦力
		physicBody->setDynamic(true);                                   //设置为动态的刚体
		physicBody->setGravityEnable(false);                            //禁用重力
		physicBody->setVelocity(Vec2(random(-300, 300), random(-300, 300)));
		physicBody->setTag(1);
		dynamicPhysicBody[num]->setPosition(Point(random(0, 1024), random(0, 768)));
		dynamicPhysicBody[num]->setPhysicsBody(physicBody);
		this->addChild(dynamicPhysicBody[num],1);
	}
}



