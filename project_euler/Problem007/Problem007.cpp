#include <iostream>
#include <cmath>
using namespace std;

class Problem007 {
public:
    void solution() {
        int target = 10001;
        int result = 1;
        int count = 1;
        while (count < target) {
            result += 2;
            if (is_prime(result)) {
                ++count;
            }
        }
        cout << result << endl;
    }

private:
    bool is_prime(int value) {
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
