#include <iostream>
#include <vector>
using namespace std;

class Problem034 {
public:
    void solution() {
        vector<int> factorials(10000);
        factorials[0] = 1;
        vector<int> auxiliary(10000);
        auxiliary[0] = 4;
        for (int i = 1; i < 10; ++i) {
            factorials[i] = factorials[i - 1] * i;
            auxiliary[i] = factorials[i] + 3;
        }

        int result = 0;
        for (int i = 10; i < 10000; ++i) {
            factorials[i] = factorials[i / 10] + factorials[i % 10];
            if (i == factorials[i]) {
                result += i;
            }
        }

        for (int i = 10; i < 100; ++i) {
            auxiliary[i] = factorials[i] + 2;
        }
        for (int i = 100; i < 1000; ++i) {
            auxiliary[i] = factorials[i] + 1;
        }
        copy(factorials.begin() + 1000, factorials.begin() + 10000, auxiliary.begin() + 1000);

        for (int i = 6 * factorials[9] + 2; i >= 10000; --i) {
            if (i == get_factorial_digit(i, factorials, auxiliary)) {
                result += i;
            }
        }
        cout << result << endl;
    }

private:
    int get_factorial_digit(int value, const vector<int> &factorials, const vector<int> &auxiliary) {
        int result = 0;
        while (value >= 10000) {
            result += auxiliary[value % 10000];
            value /= 10000;
        }
        result += factorials[value];
        return result;
    }
};
