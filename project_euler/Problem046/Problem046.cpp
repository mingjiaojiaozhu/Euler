#include <iostream>
#include <unordered_set>
#include <cmath>
using namespace std;

class Problem046 {
public:
    void solution() {
        unordered_set<int> primes(0);
        primes.insert(2);
        int result = 3;
        while (true) {
            if (is_prime(result)) {
                primes.insert(result);
            } else {
                int border = (int) sqrt((result - 1) >> 1);
                bool is_goldbach = false;
                for (int i = 1; i <= border; ++i) {
                    if (primes.find(result - (i * i << 1)) != primes.end()) {
                        is_goldbach = true;
                        break;
                    }
                }
                if (!is_goldbach) {
                    cout << result << endl;
                    return;
                }
            }
            result += 2;
        }
    }

private:
    bool is_prime(int value) {
        if (!(value & 1)) {
            return 2 == value;
        }

        int border = (int) sqrt(value);
        for (int i = 3; i <= border; i += 2) {
            if (!(value % i)) {
                return false;
            }
        }
        return 1 != value;
    }
};
