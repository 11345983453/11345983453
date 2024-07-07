

#pragma once
#include "Scrollbar.h"

class Basicwidget {
public:
    Basicwidget(int x, int y, int w, int h);
    int width();
    int height();
    void setFixedsize(int w, int h); //��������Ĵ�С
    int x();
    int y();
    void move(int x, int y);//���� ��Щ�������ʼ��λ�� λ�� 
    virtual void show() = 0; //����gui���ڵĺ���
    virtual void scroll(int mouseX, int mouseY, int wheel); // ��������
protected:
    int m_x; //����
    int m_y;
    int m_w;//���
    int m_h;
    Scrollbar vScrollbar; // ��ֱ������
    Scrollbar hScrollbar; // ˮƽ������
};

//m_x, m_y: �����λ�����ꡣ
//m_w, m_h : ����Ŀ�Ⱥ͸߶ȡ�