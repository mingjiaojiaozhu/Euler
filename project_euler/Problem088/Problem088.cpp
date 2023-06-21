#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

class Problem088 {
public:
    void solution() {
        int target = 12000;
        int length = (int) ceil(log(target) / log(2));
        vector<int> products(target - 1, (int) pow(2, length + 1));

        vector<int> digits(length, 1);
        digits[0] = 2;
        digits[1] = 2;

        int pivot = target - length;
        while (true) {
            int product = 1;
            int summation = 0;
            for (int value : digits) {
                product *= value;
                summation += value;
            }
            int difference = product - summation;
            if (difference <= pivot) {
                int index = difference + length - 2;
                if (index >= 0 && products[index] > product) {
                    products[index] = product;
                }
                ++digits[0];
            } else {
                if (!carry(digits, length)) {
                    break;
                }
            }
        }

        int result = 0;
        unordered_set<int> auxiliary(0);
        for (int value : products) {
            if (auxiliary.find(value) == auxiliary.end()) {
                result += value;
                auxiliary.insert(value);
            }
        }
        cout << result << endl;
    }

private:
    bool carry(vector<int> &digits, int length) {
        for (int i = 1; i < length; ++i) {
            if (digits[i] != digits[i - 1]) {
                ++digits[i];
                int value = digits[i];
                for (int j = 0; j < i; ++j) {
                    digits[j] = value;
                }
                return true;
            }
        }
        return false;
    }
};
