

// Scrollbar.h
#pragma once

class Scrollbar {
public:
    Scrollbar(int x, int y, int width, int height, bool isHorizontal = false);
    void scrollUp();
    void scrollDown();
    void handleScroll(int mouseX, int mouseY, int wheel);
    void draw();
    int getScrollOffset() const;

private:
    int x, y;
    int width, height;
    int scrollOffset;
    int visibleItemCount;
    int itemSize;
    int handleSize;
    int handlePos;
    bool isHorizontal; // 是否为水平滚动条
};

