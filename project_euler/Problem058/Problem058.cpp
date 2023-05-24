#include <iostream>
#include <cmath>
using namespace std;

class Problem058 {
public:
    void solution() {
        double target = 0.1;
        int index = 3;
        int count = 0;
        while (true) {
            int value = index * index;
            for (int i = 0; i < 3; ++i) {
                value -= index - 1;
                if (is_prime(value)) {
                    ++count;
                }
            }

            if ((double) count < ((index << 1) - 1) * target) {
                cout << index << endl;
                return;
            }
            index += 2;
        }
    }

private:
private:
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
