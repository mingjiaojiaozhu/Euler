#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Problem094 {
public:
    void solution() {
        int target = 1000000000;
        vector<int> index = {2, 1};
        long long result = 0L;
        while (true) {
            int auxiliary = (index[0] << 1) + index[1] * 3;
            index[1] = index[0] + (index[1] << 1);
            index[0] = auxiliary;

            int value = get_triangle(index, -1, target);
            if (-1 == value) {
                break;
            }
            result += value;

            value = get_triangle(index, 1, target);
            if (-1 == value) {
                break;
            }
            result += value;
        }
        cout << result << endl;
    }

private:
    int get_triangle(const vector<int> &index, int offset, int target) {
        int perimeter = (index[0] + offset) << 1;
        if (perimeter >= target) {
            return -1;
        }

        double length = (double) ((index[0] << 1) + offset) / 3;
        if (fabs(floor(length + 0.5) - length) > 0.00000001) {
            return 0;
        }
        double area = (length + offset) * index[1] / 2;
        if (fabs(floor(area + 0.5) - area) > 0.00000001) {
            return 0;
        }
        return perimeter;
    }
};
