#ifndef  _SecondScene_H_
#define _SecondScene_H_
#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
class SecondScene :public Layer
{
public:
	static Scene* createScene();

	//MyScene������ʼ���������� init������ִ��
	virtual bool init();

	//����һ�����󣬲�������ָ��
	CREATE_FUNC(SecondScene);

private:
	void ChangeScene(Ref* psender);
};

#endif // ! _SecondScene_H_