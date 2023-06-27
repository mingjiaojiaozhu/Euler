#include <iostream>
#include <vector>
using namespace std;

class Problem052 {
public:
    void solution() {
        int target = 6;
        vector<vector<int>> digits(2, vector<int>(10));
        int index = 10;
        while (true) {
            get_digits(index, digits[0]);
            bool is_same = true;
            for (int i = target; i > 1; --i) {
                get_digits(index * i, digits[1]);
                if (!check_digits(digits)) {
                    is_same = false;
                    break;
                }
            }
            if (is_same) {
                cout << index << endl;
                return;
            }
            ++index;
        }
    }

private:
    void get_digits(int value, vector<int> &digits) {
        digits.assign(10, 0);
        while (value) {
            ++digits[value % 10];
            value /= 10;
        }
    }

    bool check_digits(const vector<vector<int>> &digits) {
        for (int i = 0; i < 10; ++i) {
            if (digits[0][i] != digits[1][i]) {
                return false;
            }
        }
        return true;
    }
};
