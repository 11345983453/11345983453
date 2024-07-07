#include "LINKEDIT.h"
#include"Window.h"
#include<conio.h>
// ��ʾ�б༭��
void LineEdit::show()
{
    //Basicwidget::show(); // ���û����show���������ƻ����ؼ����

    setfillcolor(RGB(232, 232, 236)); // ���������ɫΪǳ��ɫ
    fillrectangle(m_x, m_y, m_x + m_w, m_y + m_h); // �����ο�

    if (!m_hideCursor)  //��� 
    {
        // ������˸��С������Ϊ���
        setlinecolor(RED); // ���ù����ɫΪ��ɫ
        line(m_x + textw + 2, m_y + 2, m_x + textw + 2, m_y + m_h - 2); // ���ƹ��
    }// ������ֵ������
    outtextxy(m_x, m_y + (m_h - textheight(m_text.c_str())) / 2, m_text.c_str()); // �����������ʾ����
    if (m_isPopUp)
    {
        m_pretext = m_text;// ��¼��ǰ�ı�
        popInputBox(); // ���������
        m_isPopUp = false;// ���õ�����־
    }
}
// �����¼�ѭ��
void LineEdit::eventLoop(const ExMessage& msg)
{
    if (msg.x > m_x && msg.x < m_x + m_w && msg.y > m_y && msg.y < m_y + m_h
        && msg.message == WM_LBUTTONDOWN) // ����Ƿ��������������
    {
        m_isPopUp = true; // ���ñ�־�Ե��������
    }
}

// ���������
void LineEdit::popInputBox()
{
    char str[128] = { 0 };
    InputBox(str, 128, nullptr, m_title.c_str(), m_text.c_str()); // ��������򣬻�ȡ�û�������ı�
    m_text = str; // �����ı�����
    textw = ::textwidth(m_text.c_str()); // �����ı����
}

// ������������
void LineEdit::setInputBoxTitle(const std::string& title)
{
    m_title = title; // ���������ı���
}

// �����ı�����
void LineEdit::setText(const std::string& text)
{
    m_text = text; // �����ı�����
    textw = ::textwidth(m_text.c_str()); // �����ı����
}

// ��ȡ��ǰ�ı�����
std::string LineEdit::text()
{
    return m_text; // ���ص�ǰ���ı�����
}

// ����ı�����
void LineEdit::clear()
{
    m_text.clear(); // ����ı�����
    textw = 0; // �����ı����
}

// ���ù������״̬
void LineEdit::setCursorHide(bool isHide)
{
    m_hideCursor = isHide; // ���ù������״̬
}

// ����ı��Ƿ�ı�
bool LineEdit::textChanged()
{
    if (m_pretext == m_text) // �Ƚϵ�ǰ�ı�����һ�ε��ı�����
    {
        return false; // �ı�����û�иı�
    }

    m_pretext = m_text; // ����ǰһ���ı�����
    return true; // �ı����ݸı���
}