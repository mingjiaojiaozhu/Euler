#include <iostream>
#include <vector>
using namespace std;

class Problem011 {
public:
    void solution() {
        vector<vector<int>> target = {{8, 2, 22, 97, 38, 15, 0, 40, 0, 75, 4, 5, 7, 78, 52, 12, 50, 77, 91, 8},
                {49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4, 56, 62, 0},
                {81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3, 49, 13, 36, 65},
                {52, 70, 95, 23, 4, 60, 11, 42, 69, 24, 68, 56, 1, 32, 56, 71, 37, 2, 36, 91},
                {22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80},
                {24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50},
                {32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70},
                {67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21},
                {24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72},
                {21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33, 95},
                {78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56, 92},
                {16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85, 57},
                {86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58},
                {19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55, 40},
                {4, 52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66},
                {88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69},
                {4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36},
                {20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4, 36, 16},
                {20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5, 54},
                {1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67, 48}};
        int size = 4;
        int length = (int) target.size();

        Product *product = new Product(1L, 0, 0);
        int result = calculate_row(target, length, size, product, 0);
        result = calculate_column(target, length, size, product, result);
        result = calculate_diagonal_left(target, length, size, product, result);
        result = calculate_diagonal_right(target, length, size, product, result);
        cout << result << endl;
    }

private:
    struct Product {
        int value;
        int index_row;
        int index_column;

        Product(int value, int index_row, int index_column): value(value), index_row(index_row), index_column(index_column) {}
    };

    int calculate_row(const vector<vector<int>> &target, int length, int size, Product *product, int pivot) {
        for (int i = 0; i < length; ++i) {
            product->value = 1;
            product->index_row = i;
            product->index_column = 0;
            multiply_row(target, length, size, product);
            if (pivot < product->value) {
                pivot = product->value;
            }

            while (product->index_column < length) {
                int value = target[product->index_row][product->index_column];
                if (value) {
                    product->value = product->value / target[product->index_row][product->index_column - size] * value;
                    ++product->index_column;
                } else {
                    product->value = 1;
                    ++product->index_column;
                    multiply_row(target, length, size, product);
                }
                if (pivot < product->value) {
                    pivot = product->value;
                }
            }
        }
        return pivot;
    }

    int calculate_column(const vector<vector<int>> &target, int length, int size, Product *product, int pivot) {
        for (int i = 0; i < length; ++i) {
            product->value = 1;
            product->index_row = 0;
            product->index_column = i;
            multiply_column(target, length, size, product);
            if (pivot < product->value) {
                pivot = product->value;
            }

            while (product->index_row < length) {
                int value = target[product->index_row][product->index_column];
                if (value) {
                    product->value = product->value / target[product->index_row - size][product->index_column] * value;
                    ++product->index_row;
                } else {
                    product->value = 1;
                    ++product->index_row;
                    multiply_column(target, length, size, product);
                }
                if (pivot < product->value) {
                    pivot = product->value;
                }
            }
        }
        return pivot;
    }

    int calculate_diagonal_left(const vector<vector<int>> &target, int length, int size, Product *product, int pivot) {
        for (int i = size - 1; i < length; ++i) {
            product->value = 1;
            product->index_row = 0;
            product->index_column = i;
            pivot = calculate_left(target, length, size, product, pivot);
        }

        for (int i = length - size; i > 0; --i) {
            product->value = 1;
            product->index_row = i;
            product->index_column = length - 1;
            pivot = calculate_left(target, length, size, product, pivot);
        }
        return pivot;
    }

    int calculate_diagonal_right(const vector<vector<int>> &target, int length, int size, Product *product, int pivot) {
        for (int i = length - size; i >= 0; --i) {
            product->value = 1;
            product->index_row = 0;
            product->index_column = i;
            pivot = calculate_right(target, length, size, product, pivot);
        }

        for (int i = length - size; i > 0; --i) {
            product->value = 1;
            product->index_row = i;
            product->index_column = 0;
            pivot = calculate_right(target, length, size, product, pivot);
        }
        return pivot;
    }

    int calculate_left(const vector<vector<int>> &target, int length, int size, Product *product, int pivot) {
        multiply_left(target, length, size, product);
        if (pivot < product->value) {
            pivot = product->value;
        }

        while (product->index_row < length && product->index_column >= 0) {
            int value = target[product->index_row][product->index_column];
            if (value) {
                product->value = product->value / target[product->index_row - size][product->index_column + size] * value;
                ++product->index_row;
                --product->index_column;
            } else {
                product->value = 1;
                ++product->index_row;
                --product->index_column;
                multiply_left(target, length, size, product);
            }
            if (pivot < product->value) {
                pivot = product->value;
            }
        }
        return pivot;
    }

    int calculate_right(const vector<vector<int>> &target, int length, int size, Product *product, int pivot) {
        multiply_right(target, length, size, product);
        if (pivot < product->value) {
            pivot = product->value;
        }

        while (product->index_row < length && product->index_column < length) {
            int value = target[product->index_row][product->index_column];
            if (value) {
                product->value = product->value / target[product->index_row - size][product->index_column - size] * value;
                ++product->index_row;
                ++product->index_column;
            } else {
                product->value = 1;
                ++product->index_row;
                ++product->index_column;
                multiply_right(target, length, size, product);
            }
            if (pivot < product->value) {
                pivot = product->value;
            }
        }
        return pivot;
    }

    void multiply_row(const vector<vector<int>> &target, int length, int size, Product *product) {
        if (product->index_column + size > length) {
            product->value = 1;
            product->index_column = length;
            return;
        }

        for (int i = 0; i < size; ++i) {
            int value = target[product->index_row][product->index_column];
            if (!value) {
                product->value = 1;
                ++product->index_column;
                multiply_row(target, length, size, product);
                return;
            }

            product->value *= value;
            ++product->index_column;
        }
    }

    void multiply_column(const vector<vector<int>> &target, int length, int size, Product *product) {
        if (product->index_row + size > length) {
            product->value = 1;
            product->index_row = length;
            return;
        }

        for (int i = 0; i < size; ++i) {
            int value = target[product->index_row][product->index_column];
            if (!value) {
                product->value = 1;
                ++product->index_row;
                multiply_column(target, length, size, product);
                return;
            }

            product->value *= value;
            ++product->index_row;
        }
    }

    void multiply_left(const vector<vector<int>> &target, int length, int size, Product *product) {
        if (product->index_row + size > length || product->index_column - size + 1 < 0) {
            product->value = 1;
            product->index_row = length;
            product->index_column = -1;
            return;
        }

        for (int i = 0; i < size; ++i) {
            int value = target[product->index_row][product->index_column];
            if (!value) {
                product->value = 1;
                ++product->index_row;
                --product->index_column;
                multiply_left(target, length, size, product);
                return;
            }

            product->value *= value;
            ++product->index_row;
            --product->index_column;
        }
    }

    void multiply_right(const vector<vector<int>> &target, int length, int size, Product *product) {
        if (product->index_row + size > length || product->index_column + size > length) {
            product->value = 1;
            product->index_row = length;
            product->index_column = length;
            return;
        }

        for (int i = 0; i < size; ++i) {
            int value = target[product->index_row][product->index_column];
            if (!value) {
                product->value = 1;
                ++product->index_row;
                ++product->index_column;
                multiply_right(target, length, size, product);
                return;
            }

            product->value *= value;
            ++product->index_row;
            ++product->index_column;
        }
    }
};
