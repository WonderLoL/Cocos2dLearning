//防止同一个头文件被多次包含    #ifndef
#ifndef _MyScene_H_
#define _MyScene_H_
#include "cocos2d.h"
#include "stdio.h"

using namespace std;
using namespace cocos2d;
USING_NS_CC;
class MyScene : public Layer
{
public:
	//通过静态scene函数，创建一个场景对象
	static Scene* createScene();

	//MyScene函数初始化工作都在 init函数中执行
	virtual bool init();

	//创建一个对象，并返回其指针
	CREATE_FUNC(MyScene);

private:
	//用来给图片菜单项打印日志
	void ImagePrint(Ref* psender);

	//用来给label菜单项打印日志
	void LabelPrint(Ref* psender);

	//用来给Font菜单项打印日志
	void FontPrint(Ref* psender);
};

#endif
