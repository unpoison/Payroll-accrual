#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Базовий клас Experience
class Experience {
private:
    int hireYear;

public:
    // Конструктор з параметром
    Experience(int hireYear) : hireYear(hireYear) {}

    // Функція для обчислення робочого досвіду
    virtual int calculateExperience() const {
        int currentYear = 2023;
        return currentYear - hireYear;
    }
};

// Похідний клас Employee, який розширює клас Experience
class Employee : public Experience {
private:
    std::string name;
    std::string position;
    double salary;

public:
    // Конструктор без параметрів
    Employee() : Experience(0), name(""), position(""), salary(0.0) {}

    // Конструктор з параметрами
    Employee(const std::string& name, const std::string& position, int hireYear, double salary)
        : Experience(hireYear), name(name), position(position), salary(salary) {}

    // Деструктор
    ~Employee() {
        // Можна додати код очищення, якщо потрібно
    }

    // Перевизначений метод для обчислення робочого досвіду
    int calculateExperience() const override {
        // Тут можна додати специфічну логіку для Employee, якщо необхідно
        return Experience::calculateExperience();
    }

    // Функція для отримання зарплати
    double getSalary() const {
        int experienceYears = calculateExperience();

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

    // Функція для отримання ім'я працівника
    const string& getName() const {
        return name;
    }
};

int main() {
    setlocale(LC_ALL, "UKR");
    vector<Employee> employees;

    // Завантаження даних з файлу (якщо файл існує)
    ifstream inputFile("employees.txt");
    if (inputFile.is_open()) {
        string name, position;
        int hireYear;
        double salary;

        while (inputFile >> name >> position >> hireYear >> salary) {
            employees.emplace_back(name, position, hireYear, salary);
        }
        inputFile.close();
    }

    int minExperience;
    cout << "Введіть мінімальний робочий досвід: ";
    cin >> minExperience;

    // Вивід на екран та запис у файл
    ofstream outputFile("filtered_employees.txt");
    bool foundEmployees = false;
    for (const Employee& emp : employees) {
        if (emp.calculateExperience() >= minExperience) {
            cout << emp.getName() << " - " << emp.getSalary() << endl;
            outputFile << emp.getName() << " - " << emp.getSalary() << endl;
            foundEmployees = true;
        }
    }

    if (!foundEmployees) {
        cout << "Працівників із таким робочим досвідом не знайдено." << endl;
    }

    outputFile.close();

    return 0;
}
