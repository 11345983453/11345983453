#include "ManageMent.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include "EmployeeData.h"
#include <string> // 确保包含这个头文件
#include <windows.h>
#include <codecvt>
#include <locale>



using namespace std;

ManageMent::ManageMent() {
    setlinecolor(BLACK);
    readRegularFile("../regular.txt");
    readTemporaryFile("../temporary.txt");
    ::loadimage(&m_bk, "../11.jpg", Window::width(), Window::height());
    ::settextstyle(26, 0, "楷体");

    menu_btns.push_back(new Button("查看正式员工信息"));
    menu_btns.push_back(new Button("增加正式员工信息"));
    menu_btns.push_back(new Button("删除正式员工信息"));
    menu_btns.push_back(new Button("修改正式员工信息"));
    menu_btns.push_back(new Button("查找正式员工信息"));

    menu_btns.push_back(new Button("查看临时员工信息"));
    menu_btns.push_back(new Button("增加临时员工信息"));
    menu_btns.push_back(new Button("删除临时员工信息"));
    menu_btns.push_back(new Button("修改临时员工信息"));
    menu_btns.push_back(new Button("查找临时员工信息"));

    menu_btns.push_back(new Button("根据金额范围查找"));
    menu_btns.push_back(new Button("排序员工信息"));
    menu_btns.push_back(new Button("退出系统"));

    for (int i = 0; i < menu_btns.size(); i++) {
        menu_btns[i]->setFixedsize(250, 50);
        menu_btns[i]->setHoverColor(RED);
        int bx = (Window::width() - menu_btns[i]->width()) / 2;
        int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
        int by = i * menu_btns[i]->height() + vspace;
        menu_btns[i]->move(bx, by);
    }
}

int ManageMent::menu() {
    for (int i = 0; i < menu_btns.size(); i++) {
        menu_btns[i]->show();
        menu_btns[i]->enentloop(m_msg);
        if (menu_btns[i]->isclicked()) {
            drawBK();
            return i;
        }
    }
    Window::flushDraw();
    return Menu;
}

void ManageMent::run() {
    op = Menu;
    Window::beginDraw();
    drawBK();
    while (1) {
        drawBK();
        if (Window::hasMsg()) {
            m_msg = Window::getMsg();
            switch (m_msg.message) {
            case WM_KEYDOWN:
                if (m_msg.vkcode = VK_ESCAPE) {
                    op = Menu;
                }
                break;
            default:
                break;
            }
        }
        switch (op) {
        case ManageMent::Menu:
            op = menu();
            break;
        case ManageMent::ShowAllRegular:
            displayAllRegular();
            break;
        case ManageMent::InsertRegular:
            insertRegular();
            break;
        case ManageMent::EraseRegular:
            eraseRegular();
            break;
        case ManageMent::UpdataTemporary:
            updateTemporary();
            break;
        case ManageMent::FindRegular:
            findRegular();
            break;
        case ManageMent::ShowAllTemporary:
            displayAllTemporary();
            break;
        case ManageMent::InsertTemporary:
            insertTemporary();
            break;
        case ManageMent::EraseTemporary:
            eraseTemporary();
            break;
        case ManageMent::UpdataRegular:
            updateRegular();
            break;
        case ManageMent::FindTemporary:
            findTemporary();
            break;
        case ManageMent::FindBySalaryRange:
            findBySalaryRange();
            break;
        case ManageMent::SortBySalary:
            sortBySalary();
            break;
        default:
            saveRegularFile("..\\regular.txt");
            saveTemporaryFile("..\\temporary.txt");
            exit(0);
            break;
        }
        Window::flushDraw();
        Window::clear();
    }
    Window::endDraw();
}

std::wstring stringToWstring(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

std::string wstringToString(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

void ManageMent::displayAllRegular() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "id", "姓名", "性别", "家庭住址", "基本工资", "岗位津贴", "养老金", "住房公积金", "医疗保险", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };

    for (const auto& emp : regularList) {
        data.push_back({
            std::to_string(emp.id),
            emp.name,
            emp.gender,
            emp.address,
            std::to_string(emp.basicSalary),
            std::to_string(emp.positionAllowance),
            std::to_string(emp.pension),
            std::to_string(emp.housingFund),
            std::to_string(emp.medicalInsurance),
            std::to_string(emp.incomeTax)
            });
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();


    ExMessage msg;
    bool exitToMenu = false;
    int i = 0;
    while (!exitToMenu)
    {
        // 如果有消息
        if (peekmessage(&msg))
        {
             /*处理鼠标滚轮消息*/
            if (msg.message == WM_MOUSEWHEEL) 
            {
                a.scroll(msg.x, msg.y, msg.wheel);
                Window::beginDraw();
                a.draw();
                Window::flushDraw();
                cout << "1" << endl;
            }
            // 检查退出条件，按下ESC键
            else if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
            {
                exitToMenu = true;
                op = Menu;  // 设置操作为返回主菜单
                cout << "3" << endl;
                break;
            }

        }
        if (op == Menu)
        {
            return;
        }

    }


}









void ManageMent::insertRegular() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "岗位津贴", "养老金", "住房公积金", "医疗保险", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };
    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "添加";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    std::string s1 = "编号姓名性别住址工资津贴养老金住房公积金医疗保险个人所得税";
    std::string s2="请以以上格式输入或按0或者不输入数据返回主界面", s3 = "您的输入有误，即将返回或按下确定";
    InputBox(str, 128, nullptr, s1.c_str(), s2.c_str());

    s2 = str;
    s2.erase(std::find_if(s2.rbegin(), s2.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s2.end());

    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }

    std::istringstream iss(s2);
    RegularEmployee b;
    if (!(iss >> b.id >> b.name >> b.gender >> b.address >> b.basicSalary >> b.positionAllowance >> b.pension >> b.housingFund >> b.medicalInsurance >> b.incomeTax)) {
        InputBox(str, 128, nullptr, s3.c_str(), "");
        Sleep(200);
        op = Menu;
        return;
    }

    regularList.push_back(b);

    data.clear();
    data.push_back(header);
    for (const auto& emp : regularList) {
        data.push_back({
            std::to_string(emp.id),
            emp.name,
            emp.gender,
            emp.address,
            std::to_string(emp.basicSalary),
            std::to_string(emp.positionAllowance),
            std::to_string(emp.pension),
            std::to_string(emp.housingFund),
            std::to_string(emp.medicalInsurance),
            std::to_string(emp.incomeTax)
            });
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();
    Sleep(2000);
}





void ManageMent::eraseRegular() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "岗位津贴", "养老金", "住房公积金", "医疗保险", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "删除";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1, s2 = "请输入你要删除的编号 按0或者不输入数据返回主界面 ";
    InputBox(str, 128, nullptr, s2.c_str(), s1.c_str());
    s2 = str;
    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }
    Sleep(100);
    int number = stoi(s2.c_str());

    for (auto it = regularList.begin(); it != regularList.end(); ) {
        if (it->getId() == number) {
            it = regularList.erase(it);
        }
        else {
            ++it;
        }
    }

    data.clear();
    data.push_back(header);
    for (const auto& emp : regularList) {
        data.push_back({
            std::to_string(emp.id),
            emp.name,
            emp.gender,
            emp.address,
            std::to_string(emp.basicSalary),
            std::to_string(emp.positionAllowance),
            std::to_string(emp.pension),
            std::to_string(emp.housingFund),
            std::to_string(emp.medicalInsurance),
            std::to_string(emp.incomeTax)
            });
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();
    Sleep(200);
}


void ManageMent::findRegular() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "岗位津贴", "养老金", "住房公积金", "医疗保险", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "查找";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1, s2 = "请输入你要查找的编号或姓名 按0或者不输入数据返回主界面 ";
    InputBox(str, 128, nullptr, s2.c_str(), s1.c_str());
    s2 = str;
    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }
    Sleep(100);

    data.clear();
    data.push_back(header);
    for (auto& b : regularList) {
        if (std::to_string(b.getId()) == s2 || b.getName() == s2) {
            data.push_back({
                std::to_string(b.id),
                b.name,
                b.gender,
                b.address,
                std::to_string(b.basicSalary),
                std::to_string(b.positionAllowance),
                std::to_string(b.pension),
                std::to_string(b.housingFund),
                std::to_string(b.medicalInsurance),
                std::to_string(b.incomeTax)
                });
        }
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();
    Sleep(1000);
}


void ManageMent::displayAllTemporary() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "奖金", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };

    for (const auto& emp : temporaryList) {
        data.push_back({
            std::to_string(emp.id),
            emp.name,
            emp.gender,
            emp.address,
            std::to_string(emp.basicSalary),
            std::to_string(emp.bonus),
            std::to_string(emp.incomeTax)
            });
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    //ExMessage msg;
    //bool exitToMenu = false;
    //while (!exitToMenu) {
    //    // 如果有消息
    //    if (peekmessage(&msg)) {
    //        // 处理鼠标滚轮消息
    //        if (msg.message == WM_MOUSEWHEEL) {
    //            a.scroll(msg.x, msg.y, msg.wheel);
    //            Window::beginDraw();
    //            a.draw();
    //            Window::flushDraw();
    //        }
    //        // 处理鼠标点击消息
    //        if (msg.message == WM_LBUTTONDOWN) {
    //            a.handleMouseClick(msg.x, msg.y);
    //        }
    //        // 检查退出条件，例如按下ESC键
    //        if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
    //            exitToMenu = true;
    //            op = Menu;  // 设置操作为返回主菜单
    //            break;
    //        }
    //    }
    //    Sleep(10); // 防止CPU占用过高
    //}
}


void ManageMent::insertTemporary() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "奖金", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "添加";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "编号姓名性别家庭住址基本工资奖金个人所得税的格式输入";
    string s2="按0或者不输入数据返回主界面", s3 = "您的输入有误，即将返回或按下确定";
    InputBox(str, 128, nullptr, s1.c_str(), s2.c_str());
    s2 = str;
    s2.erase(std::find_if(s2.rbegin(), s2.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s2.end());

    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }

    std::istringstream iss(s2);
    TemporaryEmployee b;
    if (!(iss >> b.id >> b.name >> b.gender >> b.address >> b.basicSalary >> b.bonus >> b.incomeTax)) {
        InputBox(str, 128, nullptr, s3.c_str(), "");
        Sleep(200);
        op = Menu;
        return;
    }

    temporaryList.push_back(b);

    data.clear();
    data.push_back(header);
    for (const auto& emp : temporaryList) {
        data.push_back({
            std::to_string(emp.id),
            emp.name,
            emp.gender,
            emp.address,
            std::to_string(emp.basicSalary),
            std::to_string(emp.bonus),
            std::to_string(emp.incomeTax)
            });
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();
}


void ManageMent::eraseTemporary() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "奖金", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "删除";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "请输入你要删除的编号 按0或者不输入数据返回主界面 ",s2;
    InputBox(str, 128, nullptr, s1.c_str(), s2.c_str());
    s2 = str;
    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }
    Sleep(100);
    int number = stoi(s2);

    for (auto it = temporaryList.begin(); it != temporaryList.end(); ) {
        if (it->getId() == number) {
            it = temporaryList.erase(it);
        }
        else {
            ++it;
        }
    }

    data.clear();
    data.push_back(header);
    for (const auto& emp : temporaryList) {
        data.push_back({
            std::to_string(emp.id),
            emp.name,
            emp.gender,
            emp.address,
            std::to_string(emp.basicSalary),
            std::to_string(emp.bonus),
            std::to_string(emp.incomeTax)
            });
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();
}



void ManageMent::findTemporary() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "奖金", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "查找";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "请输入你要查找的编号或姓名 按0或者不输入数据返回主界面 ";
    string s2;
    InputBox(str, 128, nullptr, s1.c_str(), s2.c_str());
    s2 = str;
    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }
    Sleep(100);

    data.clear();
    data.push_back(header);
    for (auto& b : temporaryList) {
        if (std::to_string(b.getId()) == s2 || b.getName() == s2) {
            data.push_back({
                std::to_string(b.id),
                b.name,
                b.gender,
                b.address,
                std::to_string(b.basicSalary),
                std::to_string(b.bonus),
                std::to_string(b.incomeTax)
                });
        }
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();
    Sleep(10000);
}


void ManageMent::findBySalaryRange() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "是否为正式员工", "姓名", "实发工资" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "查找";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "请输入要查找的工资范围，例如：1000 5000。";
    string s2 = "按0或者不输入数据返回主界面";
    InputBox(str, 128, nullptr, s1.c_str(), s2.c_str());
    s2 = str;
    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }
    Sleep(2000); // 增加等待时间，让用户有充足时间阅读提示信息

    int low, high;
    std::istringstream iss(s2);
    if (!(iss >> low >> high)) {
        MessageBox(nullptr, "输入格式错误，请输入正确的工资范围，例如：1000 5000。", "错误", MB_OK);
        op = Menu;
        return;
    }

    data.clear();
    data.push_back(header);
    for (auto& b : regularList) {
        double salary = b.calculateSalary();
        if (salary >= low && salary <= high) {
            data.push_back({
                std::to_string(b.id),
                "是",
                b.name,
                std::to_string(salary)
                });
        }
    }

    for (auto& b : temporaryList) {
        double salary = b.calculateSalary();
        if (salary >= low && salary <= high) {
            data.push_back({
                std::to_string(b.id),
                "否",
                b.name,
                std::to_string(salary)
                });
        }
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    // 增加等待时间，确保用户可以看到结果
    Sleep(5000); // 显示结果5秒钟
}



void ManageMent::sortBySalary() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "是否为正式员工", "姓名", "实发工资" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);

    std::vector<EmployeeData> employees;

    for (auto& b : regularList) {
        employees.push_back(EmployeeData{ b.getId(), true, b.getName(), b.calculateSalary() });
    }

    for (auto& b : temporaryList) {
        employees.push_back(EmployeeData{ b.getId(), false, b.getName(), b.calculateSalary() });
    }

    std::sort(employees.begin(), employees.end(), [](const EmployeeData& a, const EmployeeData& b) {
        return a.salary > b.salary;
        });

    data.clear();
    data.push_back(header);
    for (const auto& emp : employees) {
        data.push_back({
            std::to_string(emp.id),
            emp.isRegular ? "是" : "否",
            emp.name,
            std::to_string(emp.salary)
            });
    }

    a.setData(data);

    // Begin drawing
    Window::beginDraw();

    // Draw the table
    a.draw();

    // End drawing
    Window::flushDraw();
    Sleep(50);
    // 添加鼠标事件处理和滚动逻辑
    ExMessage msg;
    while (true) {
        // 如果有消息
        if (peekmessage(&msg)) {
            // 处理鼠标滚轮消息
            if (msg.message == WM_MOUSEWHEEL) {
                a.scroll(msg.x, msg.y, msg.wheel);
                Window::beginDraw();
                a.draw();
                Window::flushDraw();
            }
            // 处理鼠标点击消息
            if (msg.message == WM_LBUTTONDOWN) {
                a.handleMouseClick(msg.x, msg.y);
            }
            // 检查退出条件，例如按下ESC键
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
                break;
            }
        }
        Sleep(10); // 防止CPU占用过高
    }
}




void ManageMent::drawBK() {
    ::putimage(0, 0, &m_bk);
}

void ManageMent::readRegularFile(const std::string& fileName) {
    fstream read(fileName, ios::in);
    if (!read.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    char buf[1024] = { 0 };
    read.getline(buf, 1024);
    regularHead = buf;
    regularHead += "\n";
    while (!read.eof()) {
        char data[1024] = { 0 };
        read.getline(data, 1024);
        stringstream ss(data);
        RegularEmployee b;
        ss >> b.id >> b.name >> b.gender >> b.address >> b.basicSalary >> b.positionAllowance >> b.pension >> b.housingFund >> b.medicalInsurance >> b.incomeTax;
        regularList.push_back(b);
    }
    read.close();
}



void ManageMent::saveRegularFile(const std::string& fileName) {
    fstream write(fileName, ios::out | ios::trunc);
    if (!write.is_open()) {
        cerr << "无法打开文件" << endl;
        return;
    }
    write.write(regularHead.c_str(), regularHead.size());
    for (size_t i = 0; i < regularList.size(); ++i) {
        auto& b = regularList[i];
        std::string s1 = std::to_string(b.id) + " " + b.name + " " + b.gender + " " + b.address + " " + std::to_string(b.basicSalary) + " " +
            std::to_string(b.positionAllowance) + " " + std::to_string(b.pension) + " " + std::to_string(b.housingFund) + " " +
            std::to_string(b.medicalInsurance) + " " + std::to_string(b.incomeTax);
        if (i < regularList.size() - 1) {
            s1 += "\n"; // 只有在不是最后一个元素时才添加换行符
        }
        write.write(s1.c_str(), s1.size());
    }
}


void ManageMent::readTemporaryFile(const std::string& fileName) {
    fstream read(fileName, ios::in);
    if (!read.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    char buf[1024] = { 0 };
    read.getline(buf, 1024);
    temporaryHead = buf;
    temporaryHead += "\n";
    while (!read.eof()) {
        char data[1024] = { 0 };
        read.getline(data, 1024);
        stringstream ss(data);
        TemporaryEmployee b;
        ss >> b.id >> b.name >> b.gender >> b.address >> b.basicSalary >> b.bonus >> b.incomeTax;
        temporaryList.push_back(b);
    }
    read.close();
}

void ManageMent::saveTemporaryFile(const std::string& fileName) {
    fstream write(fileName, ios::out | ios::trunc);
    if (!write.is_open()) {
        cerr << "无法打开文件" << endl;
        return;
    }
    write.write(temporaryHead.c_str(), temporaryHead.size());
    for (size_t i = 0; i < temporaryList.size(); ++i) {
        auto& b = temporaryList[i];
        std::string s1 = std::to_string(b.id) + " " + b.name + " " + b.gender + " " + b.address + " " + std::to_string(b.basicSalary) + " " +
            std::to_string(b.bonus) + " " + std::to_string(b.incomeTax);
        if (i < temporaryList.size() - 1) {
            s1 += "\n"; // 只有在不是最后一个元素时才添加换行符
        }
        write.write(s1.c_str(), s1.size());
    }
}


void ManageMent::updateRegular() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "岗位津贴", "养老金", "住房公积金", "医疗保险", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };
    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "修改";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "以编号 姓名 性别 家庭住址 基本工资 岗位津贴 养老金住房公积金 医疗保险 个人所得税的格式输入，请以 按0或者不输入数据返回主界面 ";
    string s2, s3 = "您的输入有误，即将返回或按下确定";
    InputBox(str, 128, nullptr, s1.c_str(), s2.c_str());
    s2 = str;
    s2.erase(std::find_if(s2.rbegin(), s2.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s2.end());

    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }

    std::istringstream iss(s2);
    RegularEmployee newRegularEmployee;
    if (!(iss >> newRegularEmployee.id >> newRegularEmployee.name >> newRegularEmployee.gender >> newRegularEmployee.address >> newRegularEmployee.basicSalary >> newRegularEmployee.positionAllowance >> newRegularEmployee.pension >> newRegularEmployee.housingFund >> newRegularEmployee.medicalInsurance >> newRegularEmployee.incomeTax)) {
        InputBox(str, 128, nullptr, s3.c_str(), "");
        Sleep(200);
        op = Menu;
        return;
    }

    bool found = false;
    for (auto& emp : regularList) {
        if (emp.id == newRegularEmployee.id) {
            emp = newRegularEmployee;
            found = true;
            break;
        }
    }
    if (!found) {
        regularList.push_back(newRegularEmployee);
    }

    data.clear();
    data.push_back(header);
    for (const auto& emp : regularList) {
        data.push_back({
            std::to_string(emp.id),
            emp.name,
            emp.gender,
            emp.address,
            std::to_string(emp.basicSalary),
            std::to_string(emp.positionAllowance),
            std::to_string(emp.pension),
            std::to_string(emp.housingFund),
            std::to_string(emp.medicalInsurance),
            std::to_string(emp.incomeTax)
            });
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();
}

void ManageMent::updateTemporary() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "编号", "姓名", "性别", "家庭住址", "基本工资", "奖金", "个人所得税" };
    std::vector<std::vector<std::string>> data = { header };
    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "修改";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "以编号 姓名 性别 家庭住址 基本工资 奖金 个人所得税的格式输入，请以 按0或者不输入数据返回主界面 ";
    string s2, s3 = "您的输入有误，即将返回或按下确定";
    InputBox(str, 128, nullptr, s1.c_str(), s2.c_str());
    s2 = str;
    s2.erase(std::find_if(s2.rbegin(), s2.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s2.end());

    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }

    std::istringstream iss(s2);
    TemporaryEmployee newTemporaryEmployee;
    if (!(iss >> newTemporaryEmployee.id >> newTemporaryEmployee.name >> newTemporaryEmployee.gender >> newTemporaryEmployee.address >> newTemporaryEmployee.basicSalary >> newTemporaryEmployee.bonus >> newTemporaryEmployee.incomeTax)) {
        InputBox(str, 128, nullptr, s3.c_str(), "");
        Sleep(200);
        op = Menu;
        return;
    }

    bool found = false;
    for (auto& emp : temporaryList) {
        if (emp.id == newTemporaryEmployee.id) {
            emp = newTemporaryEmployee;
            found = true;
            break;
        }
    }
    if (!found) {
        temporaryList.push_back(newTemporaryEmployee);
    }

    data.clear();
    data.push_back(header);
    for (const auto& emp : temporaryList) {
        data.push_back({
            std::to_string(emp.id),
            emp.name,
            emp.gender,
            emp.address,
            std::to_string(emp.basicSalary),
            std::to_string(emp.bonus),
            std::to_string(emp.incomeTax)
            });
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();
}

