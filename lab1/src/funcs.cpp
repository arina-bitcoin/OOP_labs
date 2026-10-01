#include <iostream>
#include "funcs.hpp"

bool matrix_is_symmetric(const int* const* m, std::size_t n) {
    if (m == nullptr) { return false; }
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            if (m[i][j] != m[j][i]) {
                return false;
            }
        }
    }
    return true;
}

int matrix_trace(const int* const* m, std::size_t n) {
    if (m == nullptr || n == 0) { return 0; }
    int summ = 0;
    for (std::size_t i = 0; i < n; i++) {
        summ += m[i][i];
    }
    return summ;
}
