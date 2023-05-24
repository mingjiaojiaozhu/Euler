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
