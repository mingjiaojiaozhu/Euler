#include <iostream>
#include <cmath>
using namespace std;

class Problem069 {
public:
    void solution() {
        int target = 1000000;
        int index = 3;
        int result = 2;
        while (true) {
            if (is_prime(index)) {
                if (result * index >= target) {
                    cout << result << endl;
                    return;
                }
                result *= index;
            }
            index += 2;
        }
    }

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
