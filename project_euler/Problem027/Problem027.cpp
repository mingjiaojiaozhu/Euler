#include <iostream>
#include <cmath>
using namespace std;

class Problem027 {
public:
    void solution() {
        int target = 1000;
        int border = -1 * (target - 1);
        int result = 0;
        int pivot = 0;
        for (int i = 3; i < target; i += 2) {
            if (!is_prime(i)) {
                continue;
            }

            for (int j = border; j < target; j += 2) {
                int count = 1;
                while (is_prime(count * count + count * j + i)) {
                    ++count;
                }
                if (pivot < count) {
                    pivot = count;
                    result = i * j;
                }
            }
        }
        cout << result << endl;
    }

private:
    bool is_prime(int value) {
        if (value <= 0) {
            return false;
        }
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
