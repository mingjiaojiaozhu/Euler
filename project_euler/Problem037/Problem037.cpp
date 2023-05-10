#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem037 {
public:
    void solution() {
        int target = 1000000;
        int length = (target + 1) >> 1;
        vector<bool> primes(length, true);
        primes[0] = false;

        int border = (int) sqrt(target) + 1;
        for (int i = 3; i <= border; i += 2) {
            if (primes[i >> 1]) {
                for (int j = i * i >> 1; j < length; j += i) {
                    primes[j] = false;
                }
            }
        }

        int result = 0;
        for (int i = 11; i < target; i += 2) {
            if (primes[i >> 1] && check_digits(i) && is_truncatable(i, primes)) {
                result += i;
            }
        }
        cout << result << endl;
    }

private:
    bool check_digits(int value) {
        int remainder = value % 10;
        if (3 != remainder && 7 != remainder) {
            return false;
        }

        value /= 10;
        while (value >= 10) {
            remainder = value % 10;
            if (1 != remainder && 3 != remainder && 7 != remainder && 9 != remainder) {
                return false;
            }
            value /= 10;
        }
        return 2 == value || 3 == value || 5 == value || 7 == value;
    }

    bool is_truncatable(int value, const vector<bool> &primes) {
        int divisor = 1;
        while (value / divisor >= 10) {
            divisor *= 10;
        }

        int head = value / 10;
        int tail = value % divisor;
        while (head && tail) {
            if ((2 != head && !primes[head >> 1]) || !primes[tail >> 1]) {
                return false;
            }

            divisor /= 10;
            head /= 10;
            tail %= divisor;
        }
        return true;
    }
};
