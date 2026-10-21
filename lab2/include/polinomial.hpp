#pragma once
#include <cstddef>
#include <ostream> 

class Polynomial {
private:
    double* coeffs_ = nullptr; 
    int degree_ = -1;
    void trim() noexcept;

public:
    Polynomial();
    Polynomial(const double* coefficients, int degree);
    Polynomial(const Polynomial& other);
    Polynomial(Polynomial&& other) noexcept;
    ~Polynomial();

    Polynomial& operator=(Polynomial other);
    void swap(Polynomial& other) noexcept;

    int degree() const noexcept;
     double coeff(int i) const; 
    double evaluate(double x) const noexcept;

    void add(const Polynomial& other);
    void mul(const Polynomial& other);

    double definite_integral(double a, double b) const;
    void print(std::ostream& os) const;
};
