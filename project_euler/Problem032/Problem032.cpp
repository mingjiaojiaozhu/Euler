#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Problem032 {
public:
    void solution() {
        vector<bool> digits(9);
        unordered_set<int> products(0);
        for (int i = 1; i < 10; ++i) {
            for (int j = 10000 / i; j >= 1234; --j) {
                get_products(i, j, digits, products);
            }
        }

        for (int i = 10; i < 100; ++i) {
            for (int j = 10000 / i; j >= 123; --j) {
                get_products(i, j, digits, products);
            }
        }

        int result = 0;
        for (int product : products) {
            result += product;
        }
        cout << result << endl;
    }

private:
    void get_products(int multiplicand, int multiplier, vector<bool> &digits, unordered_set<int> &products) {
        digits.assign(9, false);
        if (is_pandigital(multiplicand, digits) && is_pandigital(multiplier, digits)) {
            int product = multiplicand * multiplier;
            if (is_pandigital(product, digits)) {
                products.insert(product);
            }
        }
    }

    bool is_pandigital(int value, vector<bool> &digits) {
        while (value) {
            int index = value % 10 - 1;
            if (index < 0 || digits[index]) {
                return false;
            }
            digits[index] = true;
            value /= 10;
        }
        return true;
    }
};
