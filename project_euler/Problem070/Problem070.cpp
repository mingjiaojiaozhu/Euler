#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem070 {
public:
    void solution() {
        int target = 10000000;
        int pivot = (int) sqrt(target);
        int start = get_previous_prime(pivot);
        int end = get_next_prime(pivot);
        vector<int> primes(0);
        primes.emplace_back(end);
        vector<int> pivots(10);
        vector<int> digits(10);
        int result = 0;
        while (true) {
            for (int prime : primes) {
                get_digits(start * prime, pivots);
                get_digits((start - 1) * (prime - 1), digits);
                if (check_digits(pivots, digits)) {
                    result = start * prime;
                }
            }

            end = get_next_prime(primes[(int) primes.size() - 1]);
            while (start * end < target) {
                primes.emplace_back(end);
                get_digits(start * end, pivots);
                get_digits((start - 1) * (end - 1), digits);
                if (check_digits(pivots, digits)) {
                    result = start * end;
                }
                end = get_next_prime(end);
            }

            if (0 != result) {
                cout << result << endl;
                return;
            }
            start = get_previous_prime(start);
        }
    }

private:
    int get_previous_prime(int value) {
        if (!(value & 1)) {
            --value;
        } else {
            value -= 2;
        }

        while (!is_prime(value)) {
            value -= 2;
        }
        return value;
    }

    int get_next_prime(int value) {
        if (!(value & 1)) {
            ++value;
        } else {
            value += 2;
        }

        while (!is_prime(value)) {
            value += 2;
        }
        return value;
    }

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
};
