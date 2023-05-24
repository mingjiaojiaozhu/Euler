#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem050 {
public:
    void solution() {
        int target = 1000000;
        vector<int> primes(0);
        primes.emplace_back(2);
        int index = 3;
        int summation = 2;
        while (summation < target) {
            if (is_prime(index)) {
                primes.emplace_back(index);
                summation += index;
            }
            index += 2;
        }

        int length = (int) primes.size();
        for (int i = length - 1; i > 0; --i) {
            int value = summation - primes[i];
            if (is_prime(value)) {
                cout << value << endl;
                return;
            }
            summation = value;

            for (int j = i; j < length; ++j) {
                value += primes[j] - primes[j - i];
                if (is_prime(value) && value < target) {
                    cout << value << endl;
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
};
