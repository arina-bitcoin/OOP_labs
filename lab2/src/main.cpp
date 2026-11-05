#include "polynomial.hpp"
#include <iostream>

int main() {
    double c1[] = {1.0, 2.0};        // 1 + 2x
    double c2[] = {0.0, 1.0, 1.0};   // x + x^2
    Polynomial a(c1, 1);
    Polynomial b(c2, 2);

    Polynomial s(a);
    s.add(b);                         // 1 + 3x + x^2
    s.print(std::cout);
    std::cout << s.evaluate(2.0) << std::endl;   // 11

    Polynomial m(a);
    m.mul(b);                         // x + 3x^2 + 2x^3
    m.print(std::cout);

    double c3[] = {0.0, 0.0, 1.0};   // x^2
    Polynomial p(c3, 2);
    std::cout << p.definite_integral(0.0, 2.0) << std::endl;  // 2.66667
    return 0;
}