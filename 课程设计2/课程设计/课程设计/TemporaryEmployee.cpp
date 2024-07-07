#include "TemporaryEmployee.h"

TemporaryEmployee::TemporaryEmployee() : Employee(), bonus(0), incomeTax(0) {}

TemporaryEmployee::TemporaryEmployee(int id, const std::string& name, const std::string& gender, const std::string& address, double basicSalary, double bonus, double incomeTax)
    : Employee(id, name, gender, address, basicSalary), bonus(bonus), incomeTax(incomeTax) {}

double TemporaryEmployee::getBonus() const {
    return bonus;
}

void TemporaryEmployee::setBonus(double bonus) {
    this->bonus = bonus;
}

double TemporaryEmployee::getIncomeTax() const {
    return incomeTax;
}

void TemporaryEmployee::setIncomeTax(double incomeTax) {
    this->incomeTax = incomeTax;
}

double TemporaryEmployee::calculateSalary() const {
    return basicSalary + bonus - incomeTax;
}
