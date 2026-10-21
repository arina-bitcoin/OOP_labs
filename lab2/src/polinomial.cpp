#include "polynomial.h"
#include <cmath>
#include <algorithm>

void Polynomial::trim() noexcept {
    while (degree_ >= 0 && coeffs_[degree_] == 0.0) {
        --degree_;
    }
    if (degree_ == -1) {
        delete[] coeffs_;
        coeffs_ = nullptr;
    }
}

Polynomial::Polynomial() : coeffs_(nullptr), degree_(-1) {}

Polynomial::Polynomial(const double* coefficients, int degree) : coeffs_(nullptr), degree_(-1) {
    if (degree < 0 || coefficients == nullptr) return;
    int d = degree;
    while (d >= 0 && coefficients[d] == 0.0) --d;
    if (d < 0) return;
    coeffs_ = new double[d + 1];
    for (int i = 0; i <= d; ++i) {
        coeffs_[i] = coefficients[i];
    }
    degree_ = d;
}

Polynomial::Polynomial(const Polynomial& other) : coeffs_(nullptr), degree_(other.degree_) {
    if (degree_ >= 0) {
        coeffs_ = new double[degree_ + 1];
        for (int i = 0; i <= degree_; i++) {
            coeffs_[i] = other.coeffs_[i];
        }
    }
}

Polynomial::Polynomial(Polynomial&& other) noexcept : coeffs_(other.coeffs_), degree_(other.degree_) {
    other.coeffs_ = nullptr;
    other.degree_ = -1;
}

Polynomial::~Polynomial() { 
    delete[] coeffs_; 
}

Polynomial& Polynomial::operator=(Polynomial other) {
    this->swap(other);
    return *this;
}

void Polynomial::swap(Polynomial& other) noexcept {
    std::swap(coeffs_, other.coeffs_);
    std::swap(degree_, other.degree_);
}

int Polynomial::degree() const noexcept {
    return degree_;
}

double Polynomial::coeff(int i) const {
    if (i < 0 || i > degree_) return 0.0;
    return coeffs_[i];
}

double Polynomial::evaluate(double x) const noexcept {
    if (degree_ == -1) return 0.0;
    double result = coeffs_[degree_];
    for (int i = degree_ - 1; i >= 0; --i) {
        result = result * x + coeffs_[i];
    }
    return result;
}

void Polynomial::add(const Polynomial& other) {
    if (other.degree_ == -1) return;
    int new_degree = std::max(degree_, other.degree_);
    double* result = new double[new_degree + 1]();
    if (degree_ >= 0) {
        for (int i = 0; i <= degree_; ++i) result[i] += coeffs_[i];
    }
    for (int i = 0; i <= other.degree_; ++i) {
        result[i] += other.coeffs_[i];
    }
    delete[] coeffs_;
    coeffs_ = result;
    degree_ = new_degree;
    trim();
}

void Polynomial::mul(const Polynomial& other) {
    if (degree_ == -1 || other.degree_ == -1) {
        delete[] coeffs_;
        coeffs_ = nullptr;
        degree_ = -1;
        return;
    }
    int new_degree = degree_ + other.degree_;
    double* result = new double[new_degree + 1]();
    for (int i = 0; i <= degree_; i++) {
        for (int j = 0; j <= other.degree_; j++) {
            result[i + j] += coeffs_[i] * other.coeffs_[j];
        }
    }
    delete[] coeffs_;
    coeffs_ = result;
    degree_ = new_degree;
    trim();
}

double Polynomial::definite_integral(double a, double b) const {
    if (degree_ == -1) return 0.0;
    double F_a = 0;
    double F_b = 0;
    for (int i = degree_; i >= 0; --i) {
        double integrated_coeff = coeffs_[i] / (i + 1);
        F_b = F_b * b + integrated_coeff;
        F_a = F_a * a + integrated_coeff;
    }
    F_b *= b;
    F_a *= a;
    return F_b - F_a;
}

void Polynomial::print(std::ostream& os) const {
    if (degree_ == -1) {
        os << 0 << '\n';
        return;
    }
    bool first = true;
    for (int i = 0; i <= degree_; ++i) {
        double c = coeffs_[i];
        if (c == 0.0) continue;
        if (first) {
            if (c < 0) os << "-";
        } else {
            os << (c < 0 ? " - " : " + ");
        }
        first = false;

        double a = std::fabs(c);
        if (i == 0 || a != 1.0) os << a;
        if (i >= 1) os << 'x';
        if (i >= 2) os << '^' << i;
    }
    os << '\n';
}
