#include "polynomial.hpp"

#include <gtest/gtest.h>

TEST(Basic, DefaultIsZero) {
    Polynomial p;
    EXPECT_EQ(p.degree(), -1);
    EXPECT_DOUBLE_EQ(p.evaluate(5.0), 0.0);
}

TEST(Basic, ConstructFromArray) {
    double c[] = {1, 2, 3};
    Polynomial p(c, 2);
    EXPECT_EQ(p.degree(), 2);
    EXPECT_DOUBLE_EQ(p.coeff(0), 1);
    EXPECT_DOUBLE_EQ(p.coeff(1), 2);
    EXPECT_DOUBLE_EQ(p.coeff(2), 3);
    EXPECT_DOUBLE_EQ(p.coeff(7), 0);
}

TEST(Basic, TrimsLeadingZeros) {
    double c[] = {1, 0, 0};
    Polynomial p(c, 2);
    EXPECT_EQ(p.degree(), 0);
}

TEST(Basic, AllZeroCoefficientsGiveZeroPolynomial) {
    double c[] = {0, 0, 0};
    Polynomial p(c, 2);
    EXPECT_EQ(p.degree(), -1);
}

TEST(Basic, Evaluate) {
    double c[] = {1, 3, 1};  // 1 + 3x + x^2
    Polynomial p(c, 2);
    EXPECT_DOUBLE_EQ(p.evaluate(2.0), 11.0);
    EXPECT_DOUBLE_EQ(p.evaluate(0.0), 1.0);
}

TEST(RuleOfFive, CopyIsDeep) {
    double ca[] = {1, 2};
    double cb[] = {5};
    Polynomial a(ca, 1);
    Polynomial b(a);
    a.add(Polynomial(cb, 0));
    EXPECT_DOUBLE_EQ(b.coeff(0), 1);
    EXPECT_DOUBLE_EQ(a.coeff(0), 6);
}

TEST(RuleOfFive, MoveEmptiesSource) {
    double c[] = {1, 2, 3};
    Polynomial a(c, 2);
    Polynomial b(static_cast<Polynomial&&>(a));
    EXPECT_EQ(b.degree(), 2);
    EXPECT_EQ(a.degree(), -1);
}

TEST(RuleOfFive, CopyAssignment) {
    double c[] = {1, 2};
    Polynomial a(c, 1);
    Polynomial b;
    b = a;
    EXPECT_EQ(b.degree(), 1);
    EXPECT_DOUBLE_EQ(b.coeff(1), 2);
    EXPECT_EQ(a.degree(), 1);
}

TEST(RuleOfFive, MoveAssignment) {
    double ca[] = {1, 2};
    double cb[] = {9};
    Polynomial a(ca, 1);
    Polynomial b(cb, 0);
    b = static_cast<Polynomial&&>(a);
    EXPECT_EQ(b.degree(), 1);
    EXPECT_EQ(a.degree(), -1);
}

TEST(RuleOfFive, SelfAssignment) {
    double c[] = {1, 2, 3};
    Polynomial a(c, 2);
    Polynomial& ref = a;
    a = ref;
    EXPECT_EQ(a.degree(), 2);
    EXPECT_DOUBLE_EQ(a.coeff(2), 3);
}

TEST(Add, Example) {
    double ca[] = {1, 2};
    double cb[] = {0, 1, 1};
    Polynomial s(ca, 1);
    s.add(Polynomial(cb, 2));
    EXPECT_EQ(s.degree(), 2);
    EXPECT_DOUBLE_EQ(s.coeff(0), 1);
    EXPECT_DOUBLE_EQ(s.coeff(1), 3);
    EXPECT_DOUBLE_EQ(s.coeff(2), 1);
}

TEST(Add, WithZeroEitherSide) {
    double c[] = {1, 2};
    Polynomial a(c, 1);
    a.add(Polynomial());
    EXPECT_EQ(a.degree(), 1);
    Polynomial z;
    z.add(Polynomial(c, 1));
    EXPECT_EQ(z.degree(), 1);
    EXPECT_DOUBLE_EQ(z.coeff(1), 2);
}

TEST(Add, CancelsToZero) {
    double ca[] = {1, 2};
    double cb[] = {-1, -2};
    Polynomial a(ca, 1);
    a.add(Polynomial(cb, 1));
    EXPECT_EQ(a.degree(), -1);
}

TEST(Add, LeadingTermsCancelReducesDegree) {
    double ca[] = {1, 2, 3};
    double cb[] = {0, 0, -3};
    Polynomial a(ca, 2);
    a.add(Polynomial(cb, 2));
    EXPECT_EQ(a.degree(), 1);
}

TEST(Add, SelfAdd) {
    double c[] = {1, 2};
    Polynomial a(c, 1);
    a.add(a);
    EXPECT_DOUBLE_EQ(a.coeff(0), 2);
    EXPECT_DOUBLE_EQ(a.coeff(1), 4);
}

TEST(Mul, Example) {
    double ca[] = {1, 2};
    double cb[] = {0, 1, 1};
    Polynomial m(ca, 1);
    m.mul(Polynomial(cb, 2));  // x + 3x^2 + 2x^3
    EXPECT_EQ(m.degree(), 3);
    EXPECT_DOUBLE_EQ(m.coeff(0), 0);
    EXPECT_DOUBLE_EQ(m.coeff(1), 1);
    EXPECT_DOUBLE_EQ(m.coeff(2), 3);
    EXPECT_DOUBLE_EQ(m.coeff(3), 2);
}

TEST(Mul, ByZero) {
    double c[] = {1, 2};
    Polynomial a(c, 1);
    a.mul(Polynomial());
    EXPECT_EQ(a.degree(), -1);
}

TEST(Mul, SelfMul) {
    double c[] = {1, 1};
    Polynomial a(c, 1);
    a.mul(a);  // 1 + 2x + x^2
    EXPECT_EQ(a.degree(), 2);
    EXPECT_DOUBLE_EQ(a.coeff(1), 2);
}

TEST(Print, Format) {
    // Без <sstream> проверяем через evaluate.
    double c[] = {1, 3, 1};
    Polynomial p(c, 2);
    EXPECT_DOUBLE_EQ(p.evaluate(0.0), 1.0);
    EXPECT_DOUBLE_EQ(p.evaluate(1.0), 5.0);
}

TEST(Print, NegativeAndZero) {
    double c[] = {-1, 0, -2};
    Polynomial p(c, 2);
    EXPECT_DOUBLE_EQ(p.evaluate(0.0), -1.0);
    EXPECT_DOUBLE_EQ(p.evaluate(1.0), -3.0);
    Polynomial z;
    EXPECT_EQ(z.degree(), -1);
}

TEST(DefiniteIntegral, XSquaredZeroToTwo) {
    double c[] = {0, 0, 1};
    Polynomial p(c, 2);
    EXPECT_NEAR(p.definite_integral(0, 2), 8.0 / 3.0, 1e-9);
}

TEST(DefiniteIntegral, Constant) {
    double c[] = {5};
    Polynomial p(c, 0);
    EXPECT_NEAR(p.definite_integral(1, 3), 10.0, 1e-9);
}

TEST(DefiniteIntegral, ZeroPolynomial) {
    EXPECT_DOUBLE_EQ(Polynomial().definite_integral(-3, 7), 0.0);
}

TEST(DefiniteIntegral, EqualBounds) {
    double c[] = {1, 2, 3};
    Polynomial p(c, 2);
    EXPECT_NEAR(p.definite_integral(2, 2), 0.0, 1e-12);
}

TEST(DefiniteIntegral, SwappedBoundsChangeSign) {
    double c[] = {1, 2, 3};
    Polynomial p(c, 2);
    EXPECT_NEAR(p.definite_integral(0, 2), -p.definite_integral(2, 0), 1e-9);
}

TEST(DefiniteIntegral, MixedPolynomial) {
    double c[] = {1, 2, 3};
    Polynomial p(c, 2);
    EXPECT_NEAR(p.definite_integral(0, 1), 3.0, 1e-9);
}

TEST(DefiniteIntegral, NegativeBounds) {
    double c1[] = {0, 1};
    Polynomial p1(c1, 1);
    EXPECT_NEAR(p1.definite_integral(-1, 1), 0.0, 1e-9);
    double c2[] = {0, 0, 1};
    Polynomial p2(c2, 2);
    EXPECT_NEAR(p2.definite_integral(-1, 1), 2.0 / 3.0, 1e-9);
}

TEST(DefiniteIntegral, DoesNotModifyPolynomial) {
    double c[] = {1, 2, 3};
    Polynomial p(c, 2);
    p.definite_integral(0, 5);
    EXPECT_EQ(p.degree(), 2);
    EXPECT_DOUBLE_EQ(p.coeff(2), 3);
}