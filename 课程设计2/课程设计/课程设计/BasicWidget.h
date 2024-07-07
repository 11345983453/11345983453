

#pragma once
#include "Scrollbar.h"

class Basicwidget {
public:
    Basicwidget(int x, int y, int w, int h);
    int width();
    int height();
    void setFixedsize(int w, int h); //设置组件的大小
    int x();
    int y();
    void move(int x, int y);//设置 这些组件的起始点位置 位置 
    virtual void show() = 0; //画到gui窗口的函数
    virtual void scroll(int mouseX, int mouseY, int wheel); // 滚动处理
protected:
    int m_x; //坐标
    int m_y;
    int m_w;//宽高
    int m_h;
    Scrollbar vScrollbar; // 垂直滚动条
    Scrollbar hScrollbar; // 水平滚动条
};

//m_x, m_y: 组件的位置坐标。
//m_w, m_h : 组件的宽度和高度。