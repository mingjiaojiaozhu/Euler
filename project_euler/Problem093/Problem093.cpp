#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

class Problem093 {
public:
    void solution() {
        vector<char> signs = {'+', '-', '*', '/'};
        vector<vector<char>> operations(0);
        get_operations(signs, operations);

        vector<int> elements = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<int> auxiliary(4);
        Arithmetic *result = new Arithmetic(0, 0);
        unordered_set<int> calculations(0);
        combination(elements, 0, 4, (int) elements.size(), auxiliary, 0, operations, result, calculations);
        cout << result->value << endl;
    }

private:
    struct Arithmetic {
        int border;
        int value;

        Arithmetic(int border, int value): border(border), value(value) {}
    };

    void get_operations(const vector<char> &signs, vector<vector<char>> &operations) {
        vector<char> auxiliary(3);
        search(signs, 3, operations, auxiliary, 0);
    }

    void combination(const vector<int> &elements, int index, int count, int length, vector<int> &auxiliary, int size, const vector<vector<char>> &operations, Arithmetic *pivot, unordered_set<int> &calculations) {
        if (count == size) {
            calculations.clear();
            permutation(auxiliary, 0, count, operations, calculations);
            int border = 1;
            while (calculations.find(border) != calculations.end()) {
                ++border;
            }
            --border;
            if (pivot->border < border) {
                pivot->border = border;
                pivot->value = 0;
                for (int value : auxiliary) {
                    pivot->value = pivot->value * 10 + value;
                }
            }
            return;
        }

        for (int i = index; i < length; ++i) {
            auxiliary[size] = elements[i];
            ++size;
            combination(elements, i + 1, count, length, auxiliary, size, operations, pivot, calculations);
            --size;
        }
    }

    void search(const vector<char> &signs, int count, vector<vector<char>> &operations, vector<char> &auxiliary, int size) {
        if (count == size) {
            operations.emplace_back(vector<char>(auxiliary));
            return;
        }

        for (char value : signs) {
            auxiliary[size] = value;
            ++size;
            search(signs, count, operations, auxiliary, size);
            --size;
        }
    }

    void permutation(vector<int> &elements, int index, int length, const vector<vector<char>> &operations, unordered_set<int> &calculations) {
        if (index == length) {
            for (vector<char> operation : operations) {
                add_calculations(calculate(operation[2], calculate(operation[1], calculate(operation[0], elements[0], elements[1]), elements[2]), elements[3]), calculations);
                add_calculations(calculate(operation[1], calculate(operation[0], elements[0], elements[1]), calculate(operation[2], elements[2], elements[3])), calculations);
                add_calculations(calculate(operation[2], calculate(operation[0], elements[0], calculate(operation[1], elements[1], elements[2])), elements[3]), calculations);
                add_calculations(calculate(operation[0], elements[0], calculate(operation[2], calculate(operation[1], elements[1], elements[2]), elements[3])), calculations);
                add_calculations(calculate(operation[0], elements[0], calculate(operation[1], elements[1], calculate(operation[2], elements[2], elements[3]))), calculations);
            }
            return;
        }

        permutation(elements, index + 1, length, operations, calculations);
        for (int i = index + 1; i < length; ++i) {
            swap(elements[index], elements[i]);
            permutation(elements, index + 1, length, operations, calculations);
            swap(elements[index], elements[i]);
        }
    }

    void add_calculations(double value, unordered_set<int> &calculations) {
        if (value > 0 && fabs(floor(value + 0.5) - value) < 0.00000001) {
            calculations.insert((int) value);
        }
    }

    double calculate(char sign, double i, double j) {
        if ('+' == sign) {
            return i + j;
        }
        if ('-' == sign) {
            return i - j;
        }
        if ('*' == sign) {
            return i * j;
        }
        if (fabs(j) < 0.00000001) {
            return -1;
        }
        return i / j;
    }
};
