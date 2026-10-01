#include <iostream>
#include "matrix_ops.hpp"
#include "funcs.hpp"


bool read_int(int& value) {
    if (!(std::cin >> value)) {
        std::cin.clear();
        return false;
    }
    return true;
}

bool read_size(std::size_t& value) {
    if (!(std::cin >> value)) {
        std::cin.clear();
        return false;
    }
    return true;
}

int main() {
    int** matrix = nullptr;
    std::size_t rows = 0;
    std::size_t cols = 0;
    int choice = -1;
    int val = 0;
    std::cout << "Добро пожаловать\n";

    while (choice != 0) {
        std::cout << "Работа с матрицей\n";
        std::cout << " 1. Создать матрицу\t 2. Заполнить значением\n";
        std::cout << " 3. Напечатать    \t 4. Алгоритм варианта\n";
        std::cout << " 0. Выход\n";
        std::cout << "Выберите пункт: ";

        if (!read_int(choice)) {
            std::cout << "Ошибка ввода. Программа завершается\n";
            if (matrix != nullptr) {
                matrix_delete(matrix, rows);
            }
            return 1;
        }

        switch (choice) {
            case 1: {
                if (matrix != nullptr) {
                    matrix_delete(matrix, rows);
                    matrix = nullptr;
                }
                std::cout << "Количество строк: ";
                if (!read_size(rows)) {
                    std::cout << "Ошибка ввода. Программа завершается\n";
                    return 1;
                }
                std::cout << "Количество столбцов: ";
                if (!read_size(cols)) {
                    std::cout << "Ошибка ввода. Программа завершается\n";
                    return 1;
                }

                if (rows <= 0 || cols <= 0) {
                    std::cout << "Ошибка: размеры должны быть положительными\n";
                } else {
                    matrix = matrix_create(rows, cols);
                    std::cout << "Матрица создана\n";
                }
                break;
            }
            case 2: {
                std::cout << "Введите значение для заполнения: ";
                if (!read_int(val)) {
                    std::cout << "Ошибка ввода. Программа завершается\n";
                    if (matrix != nullptr) {
                        matrix_delete(matrix, rows);
                    }
                    return 1;
                }
                if (matrix == nullptr) {
                    std::cout << "Сначала создайте матрицу\n";
                    break;
                }
                matrix_fill(matrix, rows, cols, val);
                std::cout << "\nМатрица заполнена значением " << val << '\n';
                break;
            }
            case 3:
                if (matrix == nullptr) {
                    std::cout << "Матрица ещё не создана\n";
                } else {
                    matrix_print(matrix, rows, cols);
                }
                break;
            case 4:
                if (matrix == nullptr) {
                    std::cout << "Матрица ещё не создана\n";
                } else if (rows != cols) {
                    std::cout << "Ошибка: вычислить след и проверить симметричность можно только для квадратной матрицы\n";
                } else {
                    int trace = matrix_trace(static_cast<const int* const*>(matrix), rows);
                    std::cout << "След матрицы " << trace << "\n";
                    bool is_symmetric = matrix_is_symmetric(static_cast<const int* const*>(matrix), rows);
                    if (is_symmetric) {
                        std::cout << "Матрица симметрична\n";
                    } else {
                        std::cout << "Матрица не симметрична\n";
                    }
                }
                break;
            case 0:
                std::cout << "Выход\n";
                break;
            default:
                std::cout << "Неверный ввод\n";
                break;
        }
    }

    if (matrix != nullptr) {
        matrix_delete(matrix, rows);
    }
    return 0;
}