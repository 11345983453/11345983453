#include "RegularEmployee.h"

RegularEmployee::RegularEmployee() : Employee(), positionAllowance(0), pension(0), housingFund(0), medicalInsurance(0), incomeTax(0) {}

RegularEmployee::RegularEmployee(int id, const std::string& name, const std::string& gender, const std::string& address, double basicSalary,
    double positionAllowance, double pension, double housingFund, double medicalInsurance, double incomeTax)
    : Employee(id, name, gender, address, basicSalary),
    positionAllowance(positionAllowance), pension(pension), housingFund(housingFund), medicalInsurance(medicalInsurance), incomeTax(incomeTax) {}

double RegularEmployee::getPositionAllowance() const {
    return positionAllowance;
}

void RegularEmployee::setPositionAllowance(double positionAllowance) {
    this->positionAllowance = positionAllowance;
}

double RegularEmployee::getPension() const {
    return pension;
}

void RegularEmployee::setPension(double pension) {
    this->pension = pension;
}

double RegularEmployee::getHousingFund() const {
    return housingFund;
}

void RegularEmployee::setHousingFund(double housingFund) {
    this->housingFund = housingFund;
}

double RegularEmployee::getMedicalInsurance() const {
    return medicalInsurance;
}

void RegularEmployee::setMedicalInsurance(double medicalInsurance) {
    this->medicalInsurance = medicalInsurance;
}

double RegularEmployee::getIncomeTax() const {
    return incomeTax;
}

void RegularEmployee::setIncomeTax(double incomeTax) {
    this->incomeTax = incomeTax;
}

double RegularEmployee::calculateSalary() const {
    return basicSalary + positionAllowance - pension - housingFund - medicalInsurance - incomeTax;
}
