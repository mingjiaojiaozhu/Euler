#include <iostream>
#include <vector>
using namespace std;

class Problem068 {
public:
    void solution() {
        int target = 10;
        vector<int> ring(0);
        int border = target >> 1;
        int start = border + 1;
        ring.emplace_back(start);
        ring.emplace_back(border);
        int summation = ((target * (target + 1) >> 1) + (border * (border + 1) >> 1)) / border;
        int pivot = summation - border - start;
        ring.emplace_back(pivot);
        for (int i = target; i > start; --i) {
            ring.emplace_back(i);
            ring.emplace_back(pivot);
            pivot = summation - pivot - i;
            ring.emplace_back(pivot);
        }

        long long result = 0L;
        for (int value : ring) {
            if (value >= 10) {
                result = result * 100 + value;
            } else {
                result = result * 10 + value;
            }
        }
        cout << result << endl;
    }
};
