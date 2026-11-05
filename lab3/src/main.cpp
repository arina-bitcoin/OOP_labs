#include <iostream>

#include "student.hpp"
#include "student_set.hpp"

int main() {
    StudentSet a;
    a.add(Student("Anna", 1));
    a.add(Student("Boris", 2));
    a += Student("Clara", 3);

    StudentSet b;
    b.add(Student("Clara", 3));
    b.add(Student("Dmitry", 4));

    std::cout << "A          = " << a << '\n';
    std::cout << "B          = " << b << '\n';
    std::cout << "A | B      = " << (a | b) << '\n';
    std::cout << "A & B      = " << (a & b) << '\n';
    std::cout << "A - B      = " << (a - b) << '\n';
    std::cout << "A == B     : " << std::boolalpha << (a == b) << '\n';
    std::cout << "A != B     : " << (a != b) << '\n';

    std::cout << "\nadd(id=1) again : " << a.add(Student("Anna", 1)) << '\n';
    std::cout << "remove(id=2)    : " << a.remove(Student("", 2)) << '\n';
    std::cout << "remove(id=99)   : " << a.remove(Student("", 99)) << '\n';
    std::cout << "A(id=3)         : " << a(Student("", 3)) << '\n';
    std::cout << "A after remove  = " << a << ", size = " << a.size() << '\n';

    StudentSet copy(a);
    copy += Student("Eve", 5);
    std::cout << "\ncopy = " << copy << '\n';
    std::cout << "A    = " << a << " (haven't changed)\n";

    StudentSet moved(std::move(copy));
    std::cout << "moved = " << moved << '\n';
    std::cout << "copy after move: empty = " << copy.empty() << '\n';

    return 0;
}