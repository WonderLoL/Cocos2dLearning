//��ֹͬһ��ͷ�ļ�����ΰ���    #ifndef
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
	//ͨ����̬scene����������һ����������
	static Scene* createScene();

	//MyScene������ʼ���������� init������ִ��
	virtual bool init();

	//����һ�����󣬲�������ָ��
	CREATE_FUNC(MyScene);

private:
	//������ͼƬ�˵����ӡ��־
	void ImagePrint(Ref* psender);

	//������label�˵����ӡ��־
	void LabelPrint(Ref* psender);

	//������Font�˵����ӡ��־
	void FontPrint(Ref* psender);
};

#endif
