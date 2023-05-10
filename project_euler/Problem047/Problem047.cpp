#include <iostream>
#include <vector>
using namespace std;

class Problem047 {
public:
    void solution() {
        int target = 4;
        int length = 200000;
        vector<int> factors(length, -1);

        int count = 0;
        for (int i = 2; i <= length; ++i) {
            if (target == get_factors(i, factors, length)) {
                ++count;
                if (target == count) {
                    cout << i - 3 << endl;
                    return;
                }
            } else {
                count = 0;
            }
        }
    }

private:
    int get_factors(int value, vector<int> &factors, int length) {
        if (-1 == factors[value - 1]) {
            long long index = value;
            while (index <= length) {
                factors[(int) index - 1] = 1;
                index *= value;
            }

            for (int i = min(value - 1, length / value); i >= 2; --i) {
                factors[value * i - 1] = factors[value - 1] + factors[i - 1];
            }
        } else {
            for (int i = min(value - 1, length / value); i >= 2; --i) {
                if (is_relatively_prime(value, i) && -1 == factors[value * i - 1]) {
                    factors[value * i - 1] = factors[value - 1] + factors[i - 1];
                }
            }
        }
        return factors[value - 1];
    }

    bool is_relatively_prime(int i, int j) {
        while (i % j) {
            int auxiliary = i % j;
            i = j;
            j = auxiliary;
        }
        return 1 == j;
    }
};
