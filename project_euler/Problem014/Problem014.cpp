#include <iostream>
#include <vector>
using namespace std;

class Problem014 {
public:
    void solution() {
        int target = 1000000;
        vector<int> chains(target, -1);
        chains[0] = 1;
        chains[1] = 2;

        for (int i = 3; i <= target; ++i) {
            get_collatz(i, chains, target);
        }

        int result = 0;
        int pivot = 0;
        for (int i = 2; i < target; ++i) {
            if (pivot < chains[i]) {
                pivot = chains[i];
                result = i + 1;
            }
        }
        cout << result << endl;
    }

private:
    int get_collatz(long long value, vector<int> &chains, int length) {
        if (value <= length && -1 != chains[(int) value - 1]) {
            return chains[(int) value - 1];
        }

        int result;
        if (value & 1) {
            result = get_collatz(3 * value + 1, chains, length) + 1;
        } else {
            result = get_collatz(value >> 1, chains, length) + 1;
        }
        if (value <= length) {
            chains[(int) value - 1] = result;
        }
        return result;
    }
};
