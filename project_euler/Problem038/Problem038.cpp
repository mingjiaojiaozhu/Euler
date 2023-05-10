#include <iostream>
#include <vector>
using namespace std;

class Problem038 {
public:
    void solution() {
        vector<bool> digits(9);
        for (int i = 9487; i >= 9234; --i) {
            digits.assign(9, false);
            if (is_pandigital(i, digits) && is_pandigital(i << 1, digits)) {
                cout << i << (i << 1) << endl;
                return;
            }
        }
    }

private:
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
