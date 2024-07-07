

#pragma once
#include"BasicWidget.h"
#include"Configure.h" //Ҫ�����ı�
class Button : public Basicwidget
{
public:
    Button(const std::string& text, int x = 0, int y = 0, int w = 900, int h = 700);
    void show();

    bool isin();
    bool isclicked();

    void enentloop(const ExMessage& msg); //�¼�ѭ��
    void setBackgroundColor(COLORREF c);  //��������ɫ 
    void setHoverColor(COLORREF c);//����ƶ��� ������ť ���ɫ����ʾ�ƶ�



protected:
    std::string m_text;
    ExMessage m_msg;
    COLORREF cur_c;
    COLORREF normal_c = RGB(232, 232, 236);//ʵ�� ����ƶ���ȥ������ ����������ɫ 
    COLORREF hover_c;//����ɫ
};

