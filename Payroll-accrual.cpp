#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Experience {
private:
    int hireYear;

public:
    // Constructor with parameter
    Experience(int hireYear) : hireYear(hireYear) {}

    // Function to calculate experience
    int calculateExperience() const {
        int currentYear = 2023;
        return currentYear - hireYear;
    }
};

class Employee {
private:
    std::string name;
    std::string position;
    Experience experience;  // Add an instance of Experience
    double salary;

public:
    // Constructor without parameters
    Employee() : name(""), position(""), experience(0), salary(0.0) {}

    // Constructor with parameters
    Employee(const std::string& name, const std::string& position, int hireYear, double salary)
        : name(name), position(position), experience(hireYear), salary(salary) {}

    ~Employee() {
        // You can add cleanup code here if needed
    }

    double getSalary() const {
        int experienceYears = experience.calculateExperience();

        if (experienceYears >= 5 && experienceYears < 10) {
            return salary * 1.05;
        }
        else if (experienceYears >= 10 && experienceYears < 15) {
            return salary * 1.1;
        }
        else if (experienceYears >= 15) {
            return salary * 1.2;
        }
        else {
            return salary;
        }
    }

    int getExperience() const {
        return experience.calculateExperience();
    }

    const std::string& getName() const {
        return name;
    }
};

int main() {
    setlocale(LC_ALL, "UKR");
    vector<Employee> employees;

    // Loading data from the file (if the file exists)
    std::ifstream inputFile("employees.txt");
    if (inputFile.is_open()) {
        std::string name, position;
        int hireYear;
        double salary;

        while (inputFile >> name >> position >> hireYear >> salary) {
            employees.emplace_back(name, position, hireYear, salary);
        }
        inputFile.close();
    }

    int minExperience;
    cout << "Enter minimum work experience: ";
    cin >> minExperience;

    // Display on the screen and write to a file
    ofstream outputFile("filtered_employees.txt");
    bool foundEmployees = false;
    for (const Employee& emp : employees) {
        if (emp.getExperience() >= minExperience) {
            cout << emp.getName() << " - " << emp.getSalary() << endl;
            outputFile << emp.getName() << " - " << emp.getSalary() << endl;
            foundEmployees = true;
        }
    }

    if (!foundEmployees) {
        cout << "Employees with such experience not found." << endl;
    }

    outputFile.close();

    return 0;
}
