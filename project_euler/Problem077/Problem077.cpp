#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem077 {
public:
    void solution() {
        int target = 5000;
        vector<int> primes(0);
        primes.emplace_back(2);
        primes.emplace_back(3);
        int result = 11;
        while (get_ways(result, primes) <= target) {
            ++result;
        }
        cout << result << endl;
    }

private:
    int get_ways(int target, vector<int> &primes) {
        int index = primes[(int) primes.size() - 1] + 2;
        while (index <= target) {
            if (is_prime(index)) {
                primes.emplace_back(index);
            }
            index += 2;
        }

        vector<int> ways(target + 1, 0);
        ways[0] = 1;
        for (int prime : primes) {
            for (int i = prime; i <= target; ++i) {
                ways[i] += ways[i - prime];
            }
        }
        return ways[target];
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
