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
	//schedule(schedule_selector(MyPhysicWorld::rayCastTest), 0.2f);              //��ѯ�����߼������б������ö�ʱ������ɣ������ȡ��������Ĺ����лᱨ��
	//shootStone();
	//ballFall();
	//createSteadyPhysicSprite();
	//createDynamicPhysicSprite();

}

//����һ������ı߿�����Ϸ�����޷��ɳ�ȥ
void MyPhysicWorld::createBgEdgePhysicSprite()
{
	auto bgSprite = Sprite::create();
	bgSprite->setPosition(centerPoint);
	auto mapFrame = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);  //�����߿���� ������1.���ӵĳ���ߴ�   2.����  3.�߿�Ŀ��
	bgSprite->setPhysicsBody(mapFrame);
	this->addChild(bgSprite);
}

//ģ����������Ĺ���
void MyPhysicWorld::ballFall()
{
	auto ballSprite = Sprite::create("ball.png");
	ballSprite->setPosition(centerPoint);
	auto ballPhysicsBody = PhysicsBody::createCircle(ballSprite->getContentSize().width/2,PhysicsMaterial(2.0f,1.5f,0.1f));
	ballPhysicsBody->setGravityEnable(true);
	ballSprite->setPhysicsBody(ballPhysicsBody);
	this->addChild(ballSprite);
}

//�����ӵ����ʯͷ,һ��Ҫע��������Ӧ��������������ײ����ײ���
void MyPhysicWorld::shootStone()
{
	auto bullet = Sprite::create("HelloWorld.png");
	bullet->setPosition(0, visibleSize.height / 2);
	auto bulletPhysicsBody = PhysicsBody::createBox(bullet->getBoundingBox().size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	bulletPhysicsBody->setGravityEnable(false);
	bulletPhysicsBody->setContactTestBitmask(0x0001);
	bulletPhysicsBody->setVelocity(Vec2(200.0f, 0.0f));
	bulletPhysicsBody->setTag(1);
	//bulletPhysicsBody->applyForce(10*Vec2(1.0f,0));                            //�������ʩ�Ӹо��е����Ⱑ
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

	//����ײ�¼���Ӽ�����
	auto contactListener = EventListenerPhysicsContact::create();   //�����������ײ�ļ�����
	contactListener->onContactBegin = CC_CALLBACK_1(MyPhysicWorld::destoryStone,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

//�ݻ�ʯͷ���Ļص�����
bool MyPhysicWorld::destoryStone(const PhysicsContact& contact)
{
	auto gameObject1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto gameObject2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
	gameObject1->removeFromParentAndCleanup(true);
	gameObject2->removeFromParentAndCleanup(true);
	return true;
}

//���߼��  ��Ϸ����ĳ�ʼ�� �������������������Ϸ���壬�ܹ��������߼��
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

//ͨ�������¼���������ʵ�������ĳ��λ�� ����һ����Ϸ������ȥ
void MyPhysicWorld::touchEvent()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [&](Touch* touch, Event* event)    //Lambda����
	{
		Vec2 point = touch->getLocation();                           //��ȡ��ǰ�����ʱ��λ��
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

//�����ѯ        ����Ҫ�ö�ʱ�������ã������ȡ��������Ĺ����лᱨ��ָ���޷���ȡ
void MyPhysicWorld::rayCastRect(float dt)                                     //���ο�������
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

//���߼�ⷽ��ĺ���      ÿһ֡��Ҫ��⣬��������Ӧ�Ķ�ʱ��
void MyPhysicWorld::rayCastTest(float dt)
{
	Scene* scene = (Scene*)getParent();
	PhysicsWorld* world = scene->getPhysicsWorld();           //��ȡ�����峡����������������
	Vec2 d(400 * cosf(angle), 300 * sinf(angle));
	Vec2 endPoint = centerPoint + d;                          //�����centerPoint    ��ֹ����endPoint
	Vec2 points[5];                                           //�����洢���߼�⵽�ĵ�
	int num = 0;
	auto func = [&points, &num](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)->bool     //Lambda���͵Ļص����� �е㿴����
	{
		if (num < 5)
		{
			char a[10];
			sprintf(a, "%d", num);
			CCLOG(a);
			points[num++] = info.contact;
		}
		return true;                  //��ʾ����ɨ��Ӵ�������״��     return false��ʾ����ɨ��, �����������Ӵ����ʱ��ᴥ�����κ������������Ϸ�����ȴ���
		//return false;                     //��⵽����Ϸ��������5���Ͳ��ڼ��������
	};

	world->rayCast(func, centerPoint, endPoint, nullptr);                    //�ڵ�ǰ���������н������ߵļ��
	if (drawNode)
	{
		removeChild(drawNode);
	}
	drawNode = DrawNode::create();                                           //����һ����ͼ����
	drawNode->drawSegment(centerPoint, endPoint, 1, Color4F::RED);           //������ʵ��ֱ��
	for (int i = 0; i <num; i++)
	{
		drawNode->drawDot(points[i], 20, Color4F(1.0f, 0, 0, 1));
	}
	addChild(drawNode);
	angle += 5.0f*(float)M_PI / 180.0f;
}

//�м�λ�����һ����̬�ĸ������
void MyPhysicWorld::createSteadyPhysicSprite()
{
	steadyPhysicBody = Sprite::create("HelloWorld.png");
	auto physicBody = PhysicsBody::createBox(steadyPhysicBody->getBoundingBox().size);     //�������壬����PhysicsMaterial������Ĭ�ϲ���
	physicBody->setDynamic(false);                          //����������Ϊ��̬���壬�����ܵ������ȵ����ã��������������
	steadyPhysicBody->setPhysicsBody(physicBody);           //����������˸������
	steadyPhysicBody->setPosition(centerPoint);
	this->addChild(steadyPhysicBody,1);
}

//���5����̬������м�ľ�̬���������ײ
void MyPhysicWorld::createDynamicPhysicSprite()
{
	for (int num = 0; num < 5; num++)
	{
		dynamicPhysicBody[num] = Sprite::create("HelloWorld.png");
		auto physicBody = PhysicsBody::createBox(dynamicPhysicBody[num]->getBoundingBox().size,PhysicsMaterial(0.1f,1.0f,0.0f));  //Material���������ֱ�Ϊ���ܶȡ���ԭ����Ħ����
		physicBody->setDynamic(true);                                   //����Ϊ��̬�ĸ���
		physicBody->setGravityEnable(false);                            //��������
		physicBody->setVelocity(Vec2(random(-300, 300), random(-300, 300)));
		physicBody->setTag(1);
		dynamicPhysicBody[num]->setPosition(Point(random(0, 1024), random(0, 768)));
		dynamicPhysicBody[num]->setPhysicsBody(physicBody);
		this->addChild(dynamicPhysicBody[num],1);
	}
}



