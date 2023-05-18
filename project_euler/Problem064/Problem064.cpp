#include <iostream>
#include <cmath>
using namespace std;

class Problem064 {
public:
    void solution() {
        int target = 10000;
        int result = 0;
        for (int i = 1; i <= target; ++i) {
            if (get_period(i) & 1) {
                ++result;
            }
        }
        cout << result << endl;
    }

private:
    int get_period(int value) {
        if (fabs(floor(sqrt(value) + 0.5) - sqrt(value)) < 0.00000001) {
            return 0;
        }

        int initial = (int) sqrt(value);
        int pivot = initial << 1;
        int current = initial;
        int offset = 0;
        int factor = 1;
        int count = 0;
        while (current != pivot) {
            offset = current * factor - offset;
            factor = (value - offset * offset) / factor;
            current = (initial + offset) / factor;
            ++count;
        }
        return count;
    }
};
