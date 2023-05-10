#include <iostream>
using namespace std;

class Problem004 {
public:
    void solution() {
        int target = 100;
        int result = 0;
        for (int i = 999; i >= target; --i) {
            for (int j = i; j >= target; --j) {
                int value = i * j;
                if (is_palindrome(value) && result < value) {
                    result = value;
                    target = j;
                    break;
                }
            }
        }
        cout << result << endl;
    }

private:
    bool is_palindrome(int value) {
        int divisor = 1;
        while (10 <= value / divisor) {
            divisor *= 10;
        }

        while (value > 1) {
            int head = value / divisor;
            int tail = value % 10;
            if (head != tail) {
                return false;
            }

            value = value % divisor / 10;
            divisor /= 100;
        }
        return true;
    }
};
