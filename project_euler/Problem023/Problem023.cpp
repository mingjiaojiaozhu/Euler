#include <iostream>
#include <unordered_set>
#include <cmath>
using namespace std;

class Problem023 {
public:
    void solution() {
        int start = 24;
        int end = 28123;
        unordered_set<int> abundants(0);
        for (int i = start >> 1; i <= start; ++i) {
            if (is_abundant(i)) {
                abundants.insert(i);
            }
        }

        int result = start * (start - 1) >> 1;
        for (int i = start + 1; i <= end; ++i) {
            bool is_non_abundant = true;
            for (int abundant : abundants) {
                if (abundants.find(i - abundant) != abundants.end()) {
                    is_non_abundant = false;
                    break;
                }
            }
            if (is_non_abundant) {
                result += i;
            }

            if (is_abundant(i)) {
                abundants.insert(i);
            }
        }
        cout << result << endl;
    }

private:
    bool is_abundant(int value) {
        int border = (int) sqrt(value);
        int summation = 1;
        for (int i = 2; i < border; ++i) {
            if (!(value % i)) {
                summation += i + value / i;
            }
        }
        if (!(value % border)) {
            summation += border;
            if (value != border * border) {
                summation += value / border;
            }
        }
        return summation > value;
    }
};
