// Scrollbar.cpp
#include "Scrollbar.h"
#include <graphics.h>

Scrollbar::Scrollbar(int x, int y, int width, int height, bool isHorizontal)
    : x(x), y(y), width(width), height(height), scrollOffset(0), visibleItemCount(10), itemSize(30), handleSize(30), handlePos(0), isHorizontal(isHorizontal) {}

void Scrollbar::scrollUp() {
    if (scrollOffset > 0) {
        scrollOffset--;
    }
    if (scrollOffset < 0) {
        scrollOffset = 0;
    }
}

void Scrollbar::scrollDown() {
    int maxScrollOffset = (isHorizontal ? width : height) / itemSize - visibleItemCount;
    if (scrollOffset < maxScrollOffset) {
        scrollOffset++;
    }
}

void Scrollbar::handleScroll(int mouseX, int mouseY, int wheel) {
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
        if (wheel > 0) {
            scrollUp();
        }
        else if (wheel < 0) {
            scrollDown();
        }
    }
}

void Scrollbar::draw() {
    setfillcolor(LIGHTGRAY);
    solidrectangle(x, y, x + width, y + height);

    int maxHandlePos = (isHorizontal ? width : height) - handleSize;
    handlePos = maxHandlePos * double(scrollOffset) / ((isHorizontal ? width : height) / itemSize - visibleItemCount);

    setfillcolor(DARKGRAY);
    if (isHorizontal) {
        solidrectangle(x + handlePos, y, x + handlePos + handleSize, y + height);
    }
    else {
        solidrectangle(x, y + handlePos, x + width, y + handlePos + handleSize);
    }
}

int Scrollbar::getScrollOffset() const {
    return scrollOffset;
}
