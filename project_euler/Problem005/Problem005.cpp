#include <iostream>
#include <vector>
using namespace std;

class Problem005 {
public:
    void solution() {
        int target = 20;
        vector<int> powers(target, 0);
        for (int i = 2; i <= target; ++i) {
            factorize(i, powers);
        }

        long long result = 1L;
        for (int i = 1; i < target; ++i) {
            for (int j = 0; j < powers[i]; ++j) {
                result *= i + 1;
            }
        }
        cout << result << endl;
    }

private:
    void factorize(int value, std::vector<int> &powers) {
        int power = 0;
        while (!(value & 1)) {
            value >>= 1;
            ++power;
        }
        if (powers[1] < power) {
            powers[1] = power;
        }

        int factor = 3;
        while (factor <= value) {
            power = 0;
            while (!(value % factor)) {
                value /= factor;
                ++power;
            }
            if (powers[factor - 1] < power) {
                powers[factor - 1] = power;
            }
            factor += 2;
        }
    }
};
