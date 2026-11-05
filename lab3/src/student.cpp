#include <student.hpp>
#include <utility>

Student::Student() : name_(new char[1]), id_(0) {
    name_[0] = '\0';
}

Student::Student(const char* name, int id)
    : name_(nullptr), id_(id) {
    if (!name) name = "";
    name_ = new char[std::strlen(name) + 1];
    std::strcpy(name_, name);
}

Student::Student(const Student& other) : id_(other.id_) {
    const char* sourceName = other.getName(); 
    name_ = new char[std::strlen(sourceName) + 1];
    std::strcpy(name_, sourceName);
}

Student::Student(Student&& other) noexcept : name_(other.name_), id_(other.id_) {
    other.name_ = nullptr;
    other.id_ = 0;
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        char* newName = new char[std::strlen(other.getName()) + 1];
        std::strcpy(newName, other.getName());
        delete[] name_;
        name_ = newName;
        id_ = other.id_;
    }
    return *this;
}

Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        std::swap(name_, other.name_);
        std::swap(id_, other.id_);
    }
    return *this;
}

bool Student::operator==(const Student& other) const {
    return id_ == other.id_;
}

Student::~Student() {
    delete[] name_;
}

int Student::getId() const {
    return id_;
}

const char* Student::getName() const {
    return name_ ? name_ : "";
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Name: " << student.getName()
       << ", ID: " << student.getId();

    return os;
}

