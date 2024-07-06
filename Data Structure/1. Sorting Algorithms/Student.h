#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

#ifndef DATASTUCTUREASS_STUDENT_H
#define DATASTUCTUREASS_STUDENT_H

class Student {
private:
    string id;
    string name;
    double gpa;

public:
    Student(string n, string i, double g) : name(std::move(n)), id(std::move(i)), gpa(g) {}

    double getGpa() const {
        return gpa;
    }

    bool operator<(const Student &other) const {
        return this->name < other.name;
    }

    bool operator>(const Student &other) const {
        return this->name > other.name;
    }

    bool operator==(const Student &other) const {
        return this->name == other.name;
    }

    Student &operator=(const Student &other) {
        this->name = other.name;
        this->id = other.id;
        this->gpa = other.gpa;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Student &student) {
        os << student.name << '\n' << student.id << '\n' << student.gpa;
        return os;
    }
};

#endif //DATASTUCTUREASS_STUDENT_H
