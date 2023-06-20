#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem035 {
public:
    void solution() {
        int target = 1000000;
        int length = (target + 1) >> 1;
        vector<bool> primes(length, true);
        primes[0] = false;

        int border = (int) sqrt(target);
        for (int i = 3; i <= border; i += 2) {
            if (primes[i >> 1]) {
                for (int j = i * i >> 1; j < length; j += i) {
                    primes[j] = false;
                }
            }
        }

        int result = 13;
        for (int i = 101; i < target; i += 2) {
            if (primes[i >> 1] && check_digits(i) && is_circular(i, primes)) {
                ++result;
            }
        }
        cout << result << endl;
    }

private:
    bool check_digits(int value) {
        while (value) {
            int remainder = value % 10;
            if (1 != remainder && 3 != remainder && 7 != remainder && 9 != remainder) {
                return false;
            }
            value /= 10;
        }
        return true;
    }

    bool is_circular(int value, const vector<bool> &primes) {
        int divisor = 1;
        int length = 1;
        while (value / divisor >= 10) {
            divisor *= 10;
            ++length;
        }

        for (int i = 1; i < length; ++i) {
            value = (value % 10) * divisor + value / 10;
            if (!primes[value >> 1]) {
                return false;
            }
        }
        return true;
    }
};
