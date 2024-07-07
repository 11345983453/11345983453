

#pragma once//����һ�ַ�ֹͷ�ļ�����ΰ����ķ�ʽ��ȷ��ͷ�ļ�ֻ�ᱻ����һ�Ρ�
#include "Configure.h"

class Window//Window�ඨ�������ڴ����͹����ڵ�һ�鷽��������
{
public:
	Window(int w, int h, int flag);
	int exec();
	void setWindowTitle(const std::string& title);
	static int width();//���ؿ��
	static int height();   //���ظ߶�
	static void clear(); //��ֹ��Ϊˢ��֡�ʶ�̫�� 
	static void beginDraw(); //�����࣬��ˢ�±����� ���������ǵ���batchdraw  ������ˢ��Ƶ��
	static void flushDraw(); //�����࣬��ˢ�±����� ���������ǵ���batchdraw  ������ˢ��Ƶ��
	static void endDraw();//�����࣬��ˢ�±����� ���������ǵ���batchdraw  ������ˢ��Ƶ�� ������Ҫһֱ��
	//ȫ����̬ ��Ϊ��һ������ ��ֻ��Ҫ���þ�����

	//�ж���û����Ϣ  ���������������� 
	inline static bool hasMsg() { return ::peekmessage(&m_msg, EM_MOUSE | EM_KEY); }
	inline static const ExMessage& getMsg() { return m_msg; }//���ص�ǰ��Ϣ

private:
	HWND m_handle;//���ھ��
	inline static ExMessage m_msg; //��Ϣ�� �� ������easyx��

};

