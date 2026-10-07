#include <gtest/gtest.h>
#include "funcs.hpp"


TEST(FuncsTest, SymmetricMatrixReturnsTrue)
{
    int r0[] = {1, 2, 3};
    int r1[] = {2, 4, 5};
    int r2[] = {3, 5, 6};
    const int* m[] = {r0, r1, r2};

    EXPECT_TRUE(matrix_is_symmetric(m, 3));
}

TEST(FuncsTest, NonSymmetricMatrixReturnsFalse)
{
    int r0[] = {1, 2};
    int r1[] = {3, 4};
    const int* m[] = {r0, r1};

    EXPECT_FALSE(matrix_is_symmetric(m, 2));
}

TEST(FuncsTest, SingleElementIsSymmetric)
{
    int r0[] = {42};
    const int* m[] = {r0};

    EXPECT_TRUE(matrix_is_symmetric(m, 1));
}

TEST(FuncsTest, TraceOfThreeByThree)
{
    int r0[] = {1, 2, 3};
    int r1[] = {4, 5, 6};
    int r2[] = {7, 8, 9};
    const int* m[] = {r0, r1, r2};

    EXPECT_EQ(matrix_trace(m, 3), 15);
}

TEST(FuncsTest, TraceOfSingleElement)
{
    int r0[] = {7};
    const int* m[] = {r0};

    EXPECT_EQ(matrix_trace(m, 1), 7);
}

TEST(FuncsTest, TraceWithNegativeValues)
{
    int r0[] = {-1, 0};
    int r1[] = {0, -2};
    const int* m[] = {r0, r1};

    EXPECT_EQ(matrix_trace(m, 2), -3);
}

TEST(FuncsTest_Fail, SymmetricNullPointerReturnsFalse)
{
    EXPECT_FALSE(matrix_is_symmetric(nullptr, 3));
}

TEST(FuncsTest_Fail, TraceNullPointerReturnsZero)
{
    EXPECT_EQ(matrix_trace(nullptr, 3), 0);
}

TEST(FuncsTest_Fail, TraceZeroSizeReturnsZero)
{
    EXPECT_EQ(matrix_trace(nullptr, 0), 0);
}