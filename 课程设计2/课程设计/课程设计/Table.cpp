#include "Table.h"
#include <vector>
#include <string>
#include <graphics.h> // ȷ�������� EasyX ��ͼ�ο�

Table::Table(int x, int y, int w, int h, int visibleRowCount)
    : x(x), y(y), width(w), height(h), visibleRowCount(visibleRowCount), scrollOffset(0) {
    rowHeight = h / visibleRowCount;
    scrollbarWidth = 20;
    handleHeight = 30;
    handleY = 0;
}

void Table::setData(const std::vector<std::vector<std::string>>& newData) {
    data = newData;
    calculateColumnWidths();
}



void Table::calculateColumnWidths() {
    columnWidths.clear();
    if (!data.empty()) {
        columnWidths.resize(data[0].size(), 0);
        for (const auto& row : data) {
            for (size_t j = 0; j < row.size(); ++j) {
                int width = textwidth(row[j].c_str());
                if (width > columnWidths[j]) {
                    columnWidths[j] = width;
                }
            }
        }
    }
    int sumWidth = 0;
    for (auto it : columnWidths)
        sumWidth += it;
    for (auto& it : columnWidths)
        it = (float)it / sumWidth * width;
}



void Table::scrollUp() {
    if (scrollOffset > 0) {
        scrollOffset--;
    }
}

void Table::scrollDown() {
    int maxScrollOffset = max(0, static_cast<int>(data.size()) - visibleRowCount - 1);
    if (scrollOffset < maxScrollOffset) {
        scrollOffset++;
    }
}

void Table::scroll(int mouseX, int mouseY, int wheel) {
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
        if (wheel > 0) {
            scrollUp();
        }
        else if (wheel < 0) {
            scrollDown();
        }
    }
}


void Table::draw() {
    setbkmode(TRANSPARENT);
    setfillcolor(WHITE);
    solidrectangle(x, y, x + width, y + height);
    setlinecolor(BLACK);
    settextstyle(12, 0, "SimSun");

    int headerY = y;
    int columnX = x;

    // ���Ʊ�ͷ
    if (!data.empty()) {
        for (int j = 0; j < data[0].size(); ++j) {
            int columnWidth = columnWidths[j];
            rectangle(columnX, headerY, columnX + columnWidth, headerY + rowHeight);
            int textX = columnX + (columnWidth - textwidth(data[0][j].c_str())) / 2;
            int textY = headerY + (rowHeight - textheight("SimSun")) / 2;
            outtextxy(textX, textY, data[0][j].c_str());
            columnX += columnWidth;
        }
    }

    // ������Ҫ���Ƶ�����
    int startRow = 1 + scrollOffset; // ������ͷ
    int endRow = min(startRow + visibleRowCount, static_cast<int>(data.size()));

    // ���Ʊ������
    for (int i = startRow; i < endRow; ++i) {
        int rowY = y + (i - scrollOffset) * rowHeight; // ��ȥ scrollOffset �Լ���ʵ�ʵ� y ����
        columnX = x;
        for (int j = 0; j < data[i].size(); ++j) {
            int columnWidth = columnWidths[j];
            fillrectangle(columnX, rowY, columnX + columnWidth, rowY + rowHeight);
            int textX = columnX + (columnWidth - textwidth(data[i][j].c_str())) / 2;
            int textY = rowY + (rowHeight - textheight("SimSun")) / 2;
            outtextxy(textX, textY, data[i][j].c_str());
            columnX += columnWidth;
        }
    }

    // ���ƹ���������
    int scrollbarX = x + width;
    setfillcolor(LIGHTGRAY);
    solidrectangle(scrollbarX, y, scrollbarX + scrollbarWidth, y + height);

    // ���㻬��λ�úʹ�С
    int handleX = scrollbarX;
    int handleWidth = scrollbarWidth;
    int maxHandleY = height - handleHeight;
    handleY = maxHandleY * double(scrollOffset) / (data.size() - visibleRowCount);

    // ���ƻ���
    setfillcolor(DARKGRAY);
    solidrectangle(handleX, y + handleY, handleX + handleWidth, y + handleY + handleHeight);
}




void Table::handleMouseClick(int mouseX, int mouseY) {
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
        int clickedRow = (mouseY - y) / rowHeight + scrollOffset;
        if (clickedRow >= 0 && clickedRow < static_cast<int>(data.size())) {
            // Implement selection logic if needed
        }
    }
}

