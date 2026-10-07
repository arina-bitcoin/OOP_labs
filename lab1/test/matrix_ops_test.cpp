#include <gtest/gtest.h>
#include "matrix_ops.hpp"


TEST(MatrixOpsTest, CreateReturnsNonNullRows)
{
    const std::size_t rows = 3;
    const std::size_t cols = 4;
    int** m = matrix_create(rows, cols);
    ASSERT_NE(m, nullptr);
    for (std::size_t i = 0; i < rows; ++i) {
        EXPECT_NE(m[i], nullptr);
    }
    matrix_delete(m, rows);
}

TEST(MatrixOpsTest, FillSetsEveryElement)
{
    const std::size_t rows = 2;
    const std::size_t cols = 3;
    int** m = matrix_create(rows, cols);
    ASSERT_NE(m, nullptr);

    matrix_fill(m, rows, cols, 7);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            EXPECT_EQ(m[i][j], 7);
        }
    }

    matrix_delete(m, rows);
}

TEST(MatrixOpsTest, FillOverwritesPreviousValues)
{
    const std::size_t rows = 2;
    const std::size_t cols = 2;
    int** m = matrix_create(rows, cols);
    ASSERT_NE(m, nullptr);

    matrix_fill(m, rows, cols, 1);
    matrix_fill(m, rows, cols, -5);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            EXPECT_EQ(m[i][j], -5);
        }
    }

    matrix_delete(m, rows);
}

TEST(MatrixOpsTest, FillSingleCell)
{
    const std::size_t rows = 1;
    const std::size_t cols = 1;
    int** m = matrix_create(rows, cols);
    ASSERT_NE(m, nullptr);

    matrix_fill(m, rows, cols, 99);

    EXPECT_EQ(m[0][0], 99);

    matrix_delete(m, rows);
}

TEST(MatrixOpsTest_Fail, FillNullPointerDoesNothing)
{
    matrix_fill(nullptr, 3, 3, 1);
    SUCCEED();
}

TEST(MatrixOpsTest_Fail, DeleteNullPointerDoesNothing)
{
    matrix_delete(nullptr, 3);
    SUCCEED();
}

TEST(MatrixOpsTest_Fail, PrintNullPointerDoesNothing)
{
    matrix_print(nullptr, 3, 3);
    SUCCEED();
}