#include"Window.h"
#include "ManageMent.h"
#include<iostream>
#include<Windows.h>//windows API头文件，实现windows特定功能



int main()
{
    SetConsoleOutputCP(CP_UTF8);//中文正常显示 ，设置控制台输出编码
    std::cout.imbue(std::locale("en_US.UTF-8"));//使用utf-8的本地化编译环境


    Window w(900, 700, 1);//1宏定义

    w.setWindowTitle("员工信息管理系统");//设置窗口标题
    ManageMent m;
    m.run();
    return w.exec();
}

