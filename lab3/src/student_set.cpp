#include <student_set.hpp>

StudentSet::StudentSet()
    : data_(nullptr), size_(0), capacity_(0) {}

StudentSet::StudentSet(const StudentSet& other)
    : data_(other.capacity_ > 0 ? new Student[other.capacity_] : nullptr),
      size_(other.size_),
      capacity_(other.capacity_) {

    for (std::size_t i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
}

StudentSet::StudentSet(StudentSet&& other) noexcept
    : data_(other.data_),
      size_(other.size_),
      capacity_(other.capacity_) {

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

void StudentSet::swap(StudentSet& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

StudentSet& StudentSet::operator=(const StudentSet& other) {
    if (this != &other) {
        StudentSet temp(other);
        swap(temp);
    }
    return *this;
}

StudentSet& StudentSet::operator=(StudentSet&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

StudentSet::~StudentSet() {delete[] data_;} 

void StudentSet::reserve(std::size_t newCapacity) {
    if (newCapacity <= capacity_) {
        return;
    }
    Student* newData = new Student[newCapacity];
    for (std::size_t i = 0; i < size_; i++) {
        newData[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}

bool StudentSet::contains(const Student& student) const {
    for (std::size_t i = 0; i < size_; i++) {
        if (data_[i] == student) {
            return true;
        }
    }
    return false;
}

bool StudentSet::add(const Student& student) {
    if (contains(student)) {
        return false;
    }
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_] = student;
    size_++;
    return true;
}

bool StudentSet::remove(const Student& student) {
    for (std::size_t i = 0; i < size_; i++) {
        if (data_[i] == student) {
            for (std::size_t j = i; j < size_ - 1; j++) {
                data_[j] = std::move(data_[j + 1]);
            }
            size_--;
            return true;
        }
    }
    return false;
}

bool StudentSet::operator()(const Student& student) const {
    return contains(student);
}

std::size_t StudentSet::size() const { return size_; }

bool StudentSet::empty() const { return size_ == 0; }

std::ostream& operator<<(std::ostream& os, const StudentSet& set) {
    os << "{ ";
    for (std::size_t i = 0; i < set.size_; i++) {
        if (i > 0) os << ", ";
        os << set.data_[i];
    }
    os << " }";
    return os;
}

StudentSet& StudentSet::operator+=(const Student& student) {
    add(student);
    return *this;
}

StudentSet& StudentSet::operator-=(const Student& student) {
    remove(student);
    return *this;
}

StudentSet StudentSet::operator|(const StudentSet& other) const {
    StudentSet result;
    for (std::size_t i = 0; i < size_; i++) {
        result.add(data_[i]);
    }
    for (std::size_t i = 0; i < other.size_; i++) {
        result.add(other.data_[i]);
    }
    return result;
}

StudentSet StudentSet::operator&(const StudentSet& other) const {
    StudentSet result;
    for (std::size_t i = 0; i < size_; i++) {
        if (other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }
    return result;
}

StudentSet StudentSet::operator-(const StudentSet& other) const {
    StudentSet result;
    for (std::size_t i = 0; i < size_; i++) {
        if (!other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }
    return result;
}

bool StudentSet::operator==(const StudentSet& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (std::size_t i = 0; i < size_; i++) {
        if (!other.contains(data_[i])) {
            return false;
        }
    }

    return true;
}

bool StudentSet::operator!=(const StudentSet& other) const {
    return !(*this == other);
}

