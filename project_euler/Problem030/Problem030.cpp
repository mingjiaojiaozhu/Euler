#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem030 {
public:
    void solution() {
        int target = 5;
        vector<int> powers(10);
        for (int i = 0; i < 10; ++i) {
            powers[i] = (int) pow(i, target);
        }

        int result = 0;
        for (int i = 6 * powers[9]; i >= 10; --i) {
            if (i == get_power_digit(i, powers)) {
                result += i;
            }
        }
        cout << result << endl;
    }

private:
    int get_power_digit(int value, const vector<int> &powers) {
        int result = 0;
        while (value) {
            result += powers[value % 10];
            value /= 10;
        }
        return result;
    }
};
