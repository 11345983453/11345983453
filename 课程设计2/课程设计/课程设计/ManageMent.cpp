#include "ManageMent.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include "EmployeeData.h"
#include <string> // ȷ���������ͷ�ļ�
#include <windows.h>
#include <codecvt>
#include <locale>



using namespace std;

ManageMent::ManageMent() {
    setlinecolor(BLACK);
    readRegularFile("../regular.txt");
    readTemporaryFile("../temporary.txt");
    ::loadimage(&m_bk, "../11.jpg", Window::width(), Window::height());
    ::settextstyle(26, 0, "����");

    menu_btns.push_back(new Button("�鿴��ʽԱ����Ϣ"));
    menu_btns.push_back(new Button("������ʽԱ����Ϣ"));
    menu_btns.push_back(new Button("ɾ����ʽԱ����Ϣ"));
    menu_btns.push_back(new Button("�޸���ʽԱ����Ϣ"));
    menu_btns.push_back(new Button("������ʽԱ����Ϣ"));

    menu_btns.push_back(new Button("�鿴��ʱԱ����Ϣ"));
    menu_btns.push_back(new Button("������ʱԱ����Ϣ"));
    menu_btns.push_back(new Button("ɾ����ʱԱ����Ϣ"));
    menu_btns.push_back(new Button("�޸���ʱԱ����Ϣ"));
    menu_btns.push_back(new Button("������ʱԱ����Ϣ"));

    menu_btns.push_back(new Button("���ݽ�Χ����"));
    menu_btns.push_back(new Button("����Ա����Ϣ"));
    menu_btns.push_back(new Button("�˳�ϵͳ"));

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
    std::vector<std::string> header = { "id", "����", "�Ա�", "��ͥסַ", "��������", "��λ����", "���Ͻ�", "ס��������", "ҽ�Ʊ���", "��������˰" };
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
        // �������Ϣ
        if (peekmessage(&msg))
        {
             /*������������Ϣ*/
            if (msg.message == WM_MOUSEWHEEL) 
            {
                a.scroll(msg.x, msg.y, msg.wheel);
                Window::beginDraw();
                a.draw();
                Window::flushDraw();
                cout << "1" << endl;
            }
            // ����˳�����������ESC��
            else if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
            {
                exitToMenu = true;
                op = Menu;  // ���ò���Ϊ�������˵�
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
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "��λ����", "���Ͻ�", "ס��������", "ҽ�Ʊ���", "��������˰" };
    std::vector<std::vector<std::string>> data = { header };
    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "���";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    std::string s1 = "��������Ա�סַ���ʽ������Ͻ�ס��������ҽ�Ʊ��ո�������˰";
    std::string s2="�������ϸ�ʽ�����0���߲��������ݷ���������", s3 = "�����������󣬼������ػ���ȷ��";
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
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "��λ����", "���Ͻ�", "ס��������", "ҽ�Ʊ���", "��������˰" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "ɾ��";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1, s2 = "��������Ҫɾ���ı�� ��0���߲��������ݷ��������� ";
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
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "��λ����", "���Ͻ�", "ס��������", "ҽ�Ʊ���", "��������˰" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "����";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1, s2 = "��������Ҫ���ҵı�Ż����� ��0���߲��������ݷ��������� ";
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
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "����", "��������˰" };
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
    //    // �������Ϣ
    //    if (peekmessage(&msg)) {
    //        // ������������Ϣ
    //        if (msg.message == WM_MOUSEWHEEL) {
    //            a.scroll(msg.x, msg.y, msg.wheel);
    //            Window::beginDraw();
    //            a.draw();
    //            Window::flushDraw();
    //        }
    //        // �����������Ϣ
    //        if (msg.message == WM_LBUTTONDOWN) {
    //            a.handleMouseClick(msg.x, msg.y);
    //        }
    //        // ����˳����������簴��ESC��
    //        if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
    //            exitToMenu = true;
    //            op = Menu;  // ���ò���Ϊ�������˵�
    //            break;
    //        }
    //    }
    //    Sleep(10); // ��ֹCPUռ�ù���
    //}
}


void ManageMent::insertTemporary() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "����", "��������˰" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "���";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "��������Ա��ͥסַ�������ʽ����������˰�ĸ�ʽ����";
    string s2="��0���߲��������ݷ���������", s3 = "�����������󣬼������ػ���ȷ��";
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
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "����", "��������˰" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "ɾ��";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "��������Ҫɾ���ı�� ��0���߲��������ݷ��������� ",s2;
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
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "����", "��������˰" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "����";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "��������Ҫ���ҵı�Ż����� ��0���߲��������ݷ��������� ";
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
    std::vector<std::string> header = { "���", "�Ƿ�Ϊ��ʽԱ��", "����", "ʵ������" };
    std::vector<std::vector<std::string>> data = { header };

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "����";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "������Ҫ���ҵĹ��ʷ�Χ�����磺1000 5000��";
    string s2 = "��0���߲��������ݷ���������";
    InputBox(str, 128, nullptr, s1.c_str(), s2.c_str());
    s2 = str;
    if (s2 == "0" || s2 == "") {
        op = Menu;
        return;
    }
    Sleep(2000); // ���ӵȴ�ʱ�䣬���û��г���ʱ���Ķ���ʾ��Ϣ

    int low, high;
    std::istringstream iss(s2);
    if (!(iss >> low >> high)) {
        MessageBox(nullptr, "�����ʽ������������ȷ�Ĺ��ʷ�Χ�����磺1000 5000��", "����", MB_OK);
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
                "��",
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
                "��",
                b.name,
                std::to_string(salary)
                });
        }
    }

    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    // ���ӵȴ�ʱ�䣬ȷ���û����Կ������
    Sleep(5000); // ��ʾ���5����
}



void ManageMent::sortBySalary() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "���", "�Ƿ�Ϊ��ʽԱ��", "����", "ʵ������" };
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
            emp.isRegular ? "��" : "��",
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
    // �������¼�����͹����߼�
    ExMessage msg;
    while (true) {
        // �������Ϣ
        if (peekmessage(&msg)) {
            // ������������Ϣ
            if (msg.message == WM_MOUSEWHEEL) {
                a.scroll(msg.x, msg.y, msg.wheel);
                Window::beginDraw();
                a.draw();
                Window::flushDraw();
            }
            // �����������Ϣ
            if (msg.message == WM_LBUTTONDOWN) {
                a.handleMouseClick(msg.x, msg.y);
            }
            // ����˳����������簴��ESC��
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
                break;
            }
        }
        Sleep(10); // ��ֹCPUռ�ù���
    }
}




void ManageMent::drawBK() {
    ::putimage(0, 0, &m_bk);
}

void ManageMent::readRegularFile(const std::string& fileName) {
    fstream read(fileName, ios::in);
    if (!read.is_open()) {
        cout << "�޷����ļ�" << endl;
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
        cerr << "�޷����ļ�" << endl;
        return;
    }
    write.write(regularHead.c_str(), regularHead.size());
    for (size_t i = 0; i < regularList.size(); ++i) {
        auto& b = regularList[i];
        std::string s1 = std::to_string(b.id) + " " + b.name + " " + b.gender + " " + b.address + " " + std::to_string(b.basicSalary) + " " +
            std::to_string(b.positionAllowance) + " " + std::to_string(b.pension) + " " + std::to_string(b.housingFund) + " " +
            std::to_string(b.medicalInsurance) + " " + std::to_string(b.incomeTax);
        if (i < regularList.size() - 1) {
            s1 += "\n"; // ֻ���ڲ������һ��Ԫ��ʱ����ӻ��з�
        }
        write.write(s1.c_str(), s1.size());
    }
}


void ManageMent::readTemporaryFile(const std::string& fileName) {
    fstream read(fileName, ios::in);
    if (!read.is_open()) {
        cout << "�޷����ļ�" << endl;
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
        cerr << "�޷����ļ�" << endl;
        return;
    }
    write.write(temporaryHead.c_str(), temporaryHead.size());
    for (size_t i = 0; i < temporaryList.size(); ++i) {
        auto& b = temporaryList[i];
        std::string s1 = std::to_string(b.id) + " " + b.name + " " + b.gender + " " + b.address + " " + std::to_string(b.basicSalary) + " " +
            std::to_string(b.bonus) + " " + std::to_string(b.incomeTax);
        if (i < temporaryList.size() - 1) {
            s1 += "\n"; // ֻ���ڲ������һ��Ԫ��ʱ����ӻ��з�
        }
        write.write(s1.c_str(), s1.size());
    }
}


void ManageMent::updateRegular() {
    Table a(100, 100, 600, 400, 10);
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "��λ����", "���Ͻ�", "ס��������", "ҽ�Ʊ���", "��������˰" };
    std::vector<std::vector<std::string>> data = { header };
    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "�޸�";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "�Ա�� ���� �Ա� ��ͥסַ �������� ��λ���� ���Ͻ�ס�������� ҽ�Ʊ��� ��������˰�ĸ�ʽ���룬���� ��0���߲��������ݷ��������� ";
    string s2, s3 = "�����������󣬼������ػ���ȷ��";
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
    std::vector<std::string> header = { "���", "����", "�Ա�", "��ͥסַ", "��������", "����", "��������˰" };
    std::vector<std::vector<std::string>> data = { header };
    a.setData(data);
    Window::beginDraw();
    a.draw();
    Window::flushDraw();

    char title[50] = "�޸�";
    outtextxy((Window::width() - textwidth(title)) / 2, 0, title);

    char str[128] = { 0 };
    string s1 = "�Ա�� ���� �Ա� ��ͥסַ �������� ���� ��������˰�ĸ�ʽ���룬���� ��0���߲��������ݷ��������� ";
    string s2, s3 = "�����������󣬼������ػ���ȷ��";
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

