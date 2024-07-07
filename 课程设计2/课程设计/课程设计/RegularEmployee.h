

#pragma once
#include "Employee.h"

class RegularEmployee : public Employee {
public:
    double positionAllowance;
    double pension;
    double housingFund;
    double medicalInsurance;
    double incomeTax;

public:
    RegularEmployee();

    RegularEmployee(int id, const std::string& name, const std::string& gender, const std::string& address, double basicSalary,
        double positionAllowance, double pension, double housingFund, double medicalInsurance, double incomeTax);

    // Getters and Setters
    double getPositionAllowance() const;
    void setPositionAllowance(double positionAllowance);

    double getPension() const;
    void setPension(double pension);

    double getHousingFund() const;
    void setHousingFund(double housingFund);

    double getMedicalInsurance() const;
    void setMedicalInsurance(double medicalInsurance);

    double getIncomeTax() const;
    void setIncomeTax(double incomeTax);

    double calculateSalary() const override;
};

