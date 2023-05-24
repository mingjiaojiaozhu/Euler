#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Problem026 {
public:
    void solution() {
        int target = 1000;
        vector<int> remainders(0);
        int result = 0;
        int pivot = 0;
        for (int i = target - 1; i >= 7; i -= 2) {
            if (is_prime(i)) {
                int count = get_digit(i, remainders);
                if (pivot < count) {
                    pivot = count;
                    result = i;
                }
                if (count == i - 1) {
                    break;
                }
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

    int get_digit(int value, vector<int> &remainders) {
        remainders.clear();
        int remainder = 1;
        while (true) {
            remainders.emplace_back(remainder);
            remainder = remainder * 10 % value;
            vector<int>::iterator position = find(remainders.begin(), remainders.end(), remainder);
            if (position != remainders.end()) {
                return (int) (remainders.size() - (position - remainders.begin()));
            }
        }
    }
};
