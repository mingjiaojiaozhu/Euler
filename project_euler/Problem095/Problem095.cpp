#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

class Problem095 {
public:
    void solution() {
        int target = 1000000;
        vector<long long> divisors(target, -1L);
        for (int i = 2; i <= target; ++i) {
            get_divisor_summation(i, divisors, target);
        }
        for (int i = 1; i < target; ++i) {
            divisors[i] -= i + 1;
        }

        int result = 0;
        int pivot = 0;
        unordered_set<int> chains(0);
        for (int i = 2; i <= target; ++i) {
            int count = get_chain(i, divisors, chains, target);
            if (pivot < count) {
                pivot = count;
                result = target;
                for (int value : chains) {
                    if (result > value) {
                        result = value;
                    }
                }
            }
        }
        cout << result << endl;
    }

private:
    void get_divisor_summation(int value, vector<long long> &divisors, int length) {
        if (-1 == divisors[value - 1]) {
            long long index = value;
            int count = 1;
            while (index <= length) {
                divisors[(int) index - 1] = ((long long) pow(value, count + 1) - 1) / (value - 1);
                index *= value;
                ++count;
            }

            for (int i = min(value - 1, length / value); i >= 2; --i) {
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1];
            }
        } else {
            for (int i = min(value - 1, length / value); i >= 2; --i) {
                if (is_relatively_prime(value, i) && -1 == divisors[value * i - 1]) {
                    divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1];
                }
            }
        }
    }

    int get_chain(long long value, const vector<long long> &divisors, unordered_set<int> &chains, int target) {
        chains.clear();
        chains.insert((int) value);

        long long pivot = value;
        int count = 0;
        while (true) {
            value = divisors[(int) value - 1];
            if (pivot == value) {
                break;
            }
            if (1 == value || value >= target || chains.find((int) value) != chains.end()) {
                return 0;
            }

            chains.insert((int) value);
            ++count;
        }
        return count;
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
