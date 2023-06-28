#include <iostream>
using namespace std;

class Problem091 {
public:
    void solution() {
        int target = 50;
        int result = target * target * 3;
        for (int i = 1; i < target; ++i) {
            for (int j = 1; j <= target; ++j) {
                int divisor = common_divisor(i, j);
                result += min((target - i) * divisor / j, j * divisor / i) << 1;
            }
        }
        cout << result << endl;
    }

private:
    int common_divisor(int i, int j) {
        while (i % j) {
            int auxiliary = i % j;
            i = j;
            j = auxiliary;
        }
        return j;
    }
};
