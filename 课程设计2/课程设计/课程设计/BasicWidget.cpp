#include "Basicwidget.h"

Basicwidget::Basicwidget(int x, int y, int w, int h)
    : m_x(x), m_y(y), m_w(w), m_h(h), vScrollbar(x + w, y, 20, h), hScrollbar(x, y + h, w, 20, true) {}

int Basicwidget::width() {
    return m_w;
}

int Basicwidget::height() {
    return m_h;
}

void Basicwidget::setFixedsize(int w, int h) {
    this->m_w = w;
    this->m_h = h;
    vScrollbar = Scrollbar(m_x + m_w, m_y, 20, m_h); // 更新滚动条位置和大小
    hScrollbar = Scrollbar(m_x, m_y + m_h, m_w, 20, true); // 更新滚动条位置和大小
}

int Basicwidget::x() {
    return m_x;
}

int Basicwidget::y() {
    return m_y;
}

void Basicwidget::move(int x, int y) {
    this->m_x = x;
    this->m_y = y;
    vScrollbar = Scrollbar(m_x + m_w, m_y, 20, m_h); // 更新滚动条位置和大小
    hScrollbar = Scrollbar(m_x, m_y + m_h, m_w, 20, true); // 更新滚动条位置和大小
}

void Basicwidget::scroll(int mouseX, int mouseY, int wheel) {
    vScrollbar.handleScroll(mouseX, mouseY, wheel);
    hScrollbar.handleScroll(mouseX, mouseY, wheel);
}