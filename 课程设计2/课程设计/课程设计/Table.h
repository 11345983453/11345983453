
#pragma once
#include "Basicwidget.h"
#include "EmployeeData.h"
#include "RegularEmployee.h"
#include "TemporaryEmployee.h"
#include <string>
#include <vector>
#include <graphics.h>
#include "Basicwidget.h"
#include "EmployeeData.h"
#include "RegularEmployee.h"




class Table {
public:
    Table(int x, int y, int w, int h, int visibleRowCount);
    void setData(const std::vector<std::vector<std::string>>& data);
    void draw();


    std::vector<std::vector<std::string>> data;
    std::vector<int> columnWidths;
    int rowHeight;
    int visibleRowCount;
    int x, y, width, height;
    int scrollOffset;
    int scrollbarWidth;
    int handleHeight;
    int handleY;

    void calculateColumnWidths();
    void scrollUp();
    void scrollDown();
    void scroll(int mouseX, int mouseY, int wheel);
    void handleMouseClick(int mouseX, int mouseY);
};
