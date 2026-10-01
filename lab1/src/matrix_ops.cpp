#include <iostream>
#include "matrix_ops.hpp"

int** matrix_create(std::size_t rows, std::size_t cols) {
    int** matrix = new int*[rows];
    for (std::size_t i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void matrix_delete(int** m, std::size_t rows) {
    if (m == nullptr) { return; }
    for (std::size_t i = 0; i < rows; ++i) {
        delete[] m[i];
    }
    delete[] m;
}

void matrix_fill(int** m, std::size_t rows, std::size_t cols, int value) {
    if (m == nullptr) { return; }
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            m[i][j] = value;
        }
    }
}

void matrix_print(const int* const* m, std::size_t rows, std::size_t cols) {
    if (m == nullptr) { return; }
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            std::cout << m[i][j] << "\t";
        }
        std::cout << "\n";
    }
}
