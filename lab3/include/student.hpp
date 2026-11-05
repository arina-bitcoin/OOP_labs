#pragma once

#include <iostream>
#include <cstring>
#include <utility>

class Student {
private:
    char* name_;
    int id_;

public:
    Student(); 
    Student(const char* name, int id);
    Student(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;
    ~Student();
    bool operator==(const Student& other) const;
    const char* getName() const;
    int getId() const;
    friend std::ostream& operator<<(
        std::ostream& os,
        const Student& student
    );
};