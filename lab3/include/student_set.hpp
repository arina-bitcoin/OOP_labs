#pragma once

#include "student.hpp"
#include <iostream>
#include <cstddef>
#include <utility>

class StudentSet {
private:
    Student* data_;
    std::size_t size_;
    std::size_t capacity_;
    void reserve(std::size_t newCapacity);
    void swap(StudentSet& other) noexcept;

public:
    StudentSet();
    StudentSet(const StudentSet& other);
    StudentSet(StudentSet&& other) noexcept;

    StudentSet& operator=(const StudentSet& other);
    StudentSet& operator=(StudentSet&& other) noexcept;
    ~StudentSet();

    bool add(const Student& student);
    bool remove(const Student& student);
    bool contains(const Student& student) const;
    bool operator()(const Student& student) const; 

    std::size_t size() const;
    bool empty() const;

    StudentSet& operator+=(const Student& student);
    StudentSet& operator-=(const Student& student);

    StudentSet operator|(const StudentSet& other) const;
    StudentSet operator&(const StudentSet& other) const;
    StudentSet operator-(const StudentSet& other) const;

    bool operator==(const StudentSet& other) const;
    bool operator!=(const StudentSet& other) const;

    friend std::ostream& operator<<(std::ostream& os, const StudentSet& set);
};