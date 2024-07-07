

#pragma once
#include "Employee.h"

class TemporaryEmployee : public Employee {
public:
    double bonus;
    double incomeTax;

public:

    TemporaryEmployee();
    TemporaryEmployee(int id, const std::string& name, const std::string& gender, const std::string& address, double basicSalary, double bonus, double incomeTax);

    // Getters and Setters
    double getBonus() const;
    void setBonus(double bonus);

    double getIncomeTax() const;
    void setIncomeTax(double incomeTax);

    double calculateSalary() const override;
};
