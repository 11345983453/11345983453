
#include "Employee.h"

Employee::Employee() : id(0), name(""), gender(""), address(""), basicSalary(0.0) {}

Employee::Employee(int id, const std::string& name, const std::string& gender, const std::string& address, double basicSalary)
    : id(id), name(name), gender(gender), address(address), basicSalary(basicSalary) {}

int Employee::getId() const {
    return id;
}

std::string Employee::getName() const {
    return name;
}

std::string Employee::getGender() const {
    return gender;
}

std::string Employee::getAddress() const {
    return address;
}

double Employee::getBasicSalary() const {
    return basicSalary;
}

void Employee::setId(int id) {
    this->id = id;
}

void Employee::setName(const std::string& name) {
    this->name = name;
}

void Employee::setGender(const std::string& gender) {
    this->gender = gender;
}

void Employee::setAddress(const std::string& address) {
    this->address = address;
}

void Employee::setBasicSalary(double basicSalary) {
    this->basicSalary = basicSalary;
}
