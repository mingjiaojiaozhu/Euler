#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem051 {
public:
    void solution() {
        int target = 8;
        vector<vector<int>> digits(3, vector<int>(0));
        vector<int> steps(0);
        vector<int> auxiliary(0);

        int result = 1111;
        while (true) {
            result = get_next_prime(result);
            if (check_digits(result, digits) && check_prime_family(result, target, digits, steps, auxiliary)) {
                cout << result << endl;
                return;
            }
        }
    }

private:
    int get_next_prime(int value) {
        if (!(value & 1)) {
            ++value;
        } else {
            value += 2;
        }

        while (!is_prime(value)) {
            value += 2;
        }
        return value;
    }

    bool check_digits(int value, vector<vector<int>> &digits) {
        for (int i = 0; i < 3; ++i) {
            digits[i].clear();
        }

        value /= 10;
        int count = 1;
        while (value) {
            int remainder = value % 10;
            if (!remainder || 1 == remainder || 2 == remainder) {
                digits[remainder].emplace_back(count);
            }
            value /= 10;
            ++count;
        }

        for (const vector<int> &digit : digits) {
            if ((int) digit.size() >= 3) {
                return true;
            }
        }
        return false;
    }

    bool check_prime_family(int pivot, int target, const vector<vector<int>> &digits, vector<int> &steps, vector<int> &auxiliary) {
        bool is_family = false;
        for (int i = 0; i < 3; ++i) {
            if ((int) digits[i].size() < 3) {
                continue;
            }

            steps.clear();
            auxiliary.clear();
            combination(digits[i], 0, 3, (int) digits[i].size(), steps, auxiliary);
            for (int step : steps) {
                int count = 10 - target - i;
                int value = pivot;
                for (int j = i; j < 9; ++j) {
                    value += step;
                    if (!is_prime(value)) {
                        --count;
                    }
                    if (count < 0) {
                        break;
                    }
                }
                is_family = !count;
            }
        }
        return is_family;
    }

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

    void combination(const vector<int> &digits, int start, int count, int length, vector<int> &steps, vector<int> &auxiliary) {
        if (count == (int) auxiliary.size()) {
            int value = 0;
            for (int digit : auxiliary) {
                value += digit;
            }
            steps.emplace_back(value);
            return;
        }

        for (int i = start; i < length; ++i) {
            auxiliary.emplace_back((int) pow(10, digits[i]));
            combination(digits, i + 1, count, length, steps, auxiliary);
            auxiliary.pop_back();
        }
    }
};
