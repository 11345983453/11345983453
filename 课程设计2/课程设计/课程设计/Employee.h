
#pragma once
#include <string>

class Employee {
public:
    int id;
    std::string name;
    std::string gender;
    std::string address;
    double basicSalary;

public: 
    Employee();
    Employee(int id, const std::string& name, const std::string& gender, const std::string& address, double basicSalary);
    virtual ~Employee() = default;

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getGender() const;
    std::string getAddress() const;
    double getBasicSalary() const;

    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setGender(const std::string& gender);
    void setAddress(const std::string& address);
    void setBasicSalary(double basicSalary);

    virtual double calculateSalary() const = 0; // Pure virtual function
};
