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
	void createBgEdgePhysicSprite();                       //����һ����������߿�
	void ballFall();                                       //ģ��������Ĺ���
	void shootStone();                                     //���ʯ��
	void initRayCastTestObject();                          //��ʼ������������ײ����Ϸ����
	void touchEvent();                                     //ͨ�������ĳ��λ�ã���̷�����Ϸ����
	void rayCastTest(float dt);                            //�õ���������ʽ������
	void rayCastRect(float dt);                            //���ο�������
	bool destoryStone(const PhysicsContact& contact);      //��ײ����ݻ�ʯ��
	void createSteadyPhysicSprite();                       //������̬����Ϸ����
	void createDynamicPhysicSprite();                      //������̬����Ϸ����
};
#endif