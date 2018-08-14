#ifndef  _SecondScene_H_
#define _SecondScene_H_
#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
class SecondScene :public Layer
{
public:
	static Scene* createScene();

	//MyScene函数初始化工作都在 init函数中执行
	virtual bool init();

	//创建一个对象，并返回其指针
	CREATE_FUNC(SecondScene);

private:
	void ChangeScene(Ref* psender);
};

#endif // ! _SecondScene_H_