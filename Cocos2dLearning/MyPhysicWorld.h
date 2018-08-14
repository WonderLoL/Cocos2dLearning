#ifndef _MyPhysicWorld_H_
#define _MyPhysicWorld_H_
#include "Cocos2d.h"
using namespace cocos2d;

class MyPhysicWorld :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MyPhysicWorld);
private:
	Sprite* steadyPhysicBody;
	Sprite* dynamicPhysicBody[5];
	Sprite* rayCastPhysicBody;
	Sprite* rayCastPhysicBody1;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point centerPoint = Point(visibleSize.width / 2, visibleSize.height / 2);
	float angle = 0.0f;
	DrawNode* drawNode;
	void createBgEdgePhysicSprite();                       //创建一个背景物理边框
	void ballFall();                                       //模拟球下落的过程
	void shootStone();                                     //射击石块
	void initRayCastTestObject();                          //初始化两个射线碰撞的游戏物体
	void touchEvent();                                     //通过鼠标点击某个位置，相继放置游戏物体
	void rayCastTest(float dt);                            //用调度器的形式来调用
	void rayCastRect(float dt);                            //矩形框物理检测
	bool destoryStone(const PhysicsContact& contact);      //碰撞检测后摧毁石块
	void createSteadyPhysicSprite();                       //创建静态的游戏刚体
	void createDynamicPhysicSprite();                      //创建动态的游戏刚体
};
#endif