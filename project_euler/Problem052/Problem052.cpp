#include <iostream>
#include <vector>
using namespace std;

class Problem052 {
public:
    void solution() {
        int target = 6;
        vector<int> pivots(10);
        vector<int> digits(10);
        int index = 10;
        while (true) {
            get_digits(index, pivots);
            bool is_same = true;
            for (int i = target; i > 1; --i) {
                get_digits(index * i, digits);
                if (!check_digits(pivots, digits)) {
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

    bool check_digits(const vector<int> &pivots, const vector<int> &digits) {
        for (int i = 0; i < 10; ++i) {
            if (pivots[i] != digits[i]) {
                return false;
            }
        }
        return true;
    }
};
