#include <iostream>
#include <cmath>
using namespace std;

class Problem085 {
public:
    void solution() {
        int target = 2000000;
        int border = ((int) sqrt(1 + 8 * sqrt(target)) - 1) >> 1;
        int result = 0;
        int pivot = target;
        for (int i = 1; i <= border; ++i) {
            int length = ((int) sqrt(1 + (double) (target << 4) / i / (i + 1)) - 1) >> 1;
            int value = min(abs(get_count(length, i) - target), abs(get_count(length + 1, i) - target));
            if (pivot > value) {
                result = length * i;
                pivot = value;
            }
        }
        cout << result << endl;
    }

private:
    int get_count(int length, int width) {
        return length * (length + 1) * width * (width + 1) >> 2;
    }
};
