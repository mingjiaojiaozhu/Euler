#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem049 {
public:
    void solution() {
        int target = 3330;
        int other = 1487;
        vector<int> terms(2);
        vector<bool> digits(10);
        for (int i = 10000 - (target << 1) - 1; i > 1000; i -= 2) {
            if (is_prime(i) && i != other) {
                terms[0] = i + target;
                terms[1] = terms[0] + target;
                if (is_prime(terms[0]) && is_prime(terms[1]) && check_digit(i, terms, digits)) {
                    cout << i << terms[0] << terms[1] << endl;
                    return;
                }
            }
        }
    }

private:
    bool is_prime(int value) {
        if (1 != value % 6 && 5 != value % 6) {
            return 2 == value || 3 == value;
        }

        int border = (int) sqrt(value);
        for (int i = 5; i <= border; i += 6) {
            if (!(value % i) || !(value % (i + 2))) {
                return false;
            }
        }
        return 1 != value;
    }

    bool check_digit(int value, vector<int> &terms, vector<bool> &digits) {
        digits.assign(10, false);
        while (value) {
            digits[value % 10] = true;
            value /= 10;
        }

        for (int term : terms) {
            while (term) {
                if (!digits[term % 10]) {
                    return false;
                }
                term /= 10;
            }
        }
        return true;
    }
};
