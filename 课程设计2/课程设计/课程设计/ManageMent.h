

// ManageMent.h
#pragma once
#include "Window.h"
#include <vector>
#include "Button.h"
#include "RegularEmployee.h"
#include "TemporaryEmployee.h"
#include "Table.h"
#include "LINKEDIT.h"
#include "EmployeeData.h"

class ManageMent {
    enum Operator {
        ShowAllRegular,
        InsertRegular,
        EraseRegular,
        UpdataRegular,
        FindRegular,
        ShowAllTemporary,
        InsertTemporary,
        EraseTemporary,
        UpdataTemporary,
        FindTemporary,
        FindBySalaryRange,
        SortBySalary,
        Exit,
        Menu,
    };
public:
    int op;
    ManageMent();
    int menu();
    void run();

    void displayAllRegular();
    void insertRegular();
    void eraseRegular();
    void findRegular();
    void displayAllTemporary();
    void insertTemporary();
    void eraseTemporary();
    void findTemporary();
    void findBySalaryRange();
    void sortBySalary();

    void drawBK();
    void eventLoop();

    void readRegularFile(const std::string& fileName);
    void saveRegularFile(const std::string& fileName);
    void readTemporaryFile(const std::string& fileName);
    void saveTemporaryFile(const std::string& fileName);

    void updateRegular();
    void updateTemporary();


private:
    IMAGE m_bk;
    ExMessage m_msg;
    std::vector<Button*> menu_btns;

public:
    std::string regularHead;
    std::vector<RegularEmployee> regularList;

    std::string temporaryHead;
    std::vector<TemporaryEmployee> temporaryList;

    Table* m_showTable;

public:
    LineEdit* delEdit;
    Button* delBtn;
    Table* delTable;
};

