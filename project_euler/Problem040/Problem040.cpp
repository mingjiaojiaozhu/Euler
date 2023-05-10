#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem040 {
public:
    void solution() {
        int target = 1000000;
        vector<int> borders(0);
        int index = 0;
        while (true) {
            int value = ((int) pow(10, index) * (9 * index - 1) + 1) / 9;
            borders.emplace_back(value);
            if (value > target) {
                break;
            }
            ++index;
        }

        int result = 1;
        while (target) {
            result *= get_champernowne(target, borders);
            target /= 10;
        }
        cout << result << endl;
    }

private:
    int get_champernowne(int value, const vector<int> &borders) {
        int index = get_index(value, borders) - 1;
        value -= borders[index] + 1;
        int digit = (int) pow(10, index) + value / (index + 1);
        for (int i = value % (index + 1); i < index; ++i) {
            digit /= 10;
        }
        return digit % 10;
    }

    int get_index(int value, const vector<int> &borders) {
        int start = 0;
        int end = (int) borders.size() - 1;
        while (start <= end) {
            int current = start + ((end - start) >> 1);
            if (borders[current] <= value) {
                start = current + 1;
            } else {
                end = current - 1;
            }
        }
        return start;
    }
};
