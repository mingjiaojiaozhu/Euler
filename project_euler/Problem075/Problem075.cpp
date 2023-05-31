#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;

class Problem075 {
public:
    void solution() {
        int target = 1500000;
        int border = (int) sqrt(target >> 1);
        unordered_map<int, int> perimeters(0);
        for (int i = 2; i <= border; ++i) {
            for (int j = 1; j < i; ++j) {
                if (((i + j) & 1) && is_relatively_prime(i, j)) {
                    int pivot = i * (i + j) << 1;
                    int length = pivot;
                    while (length < target) {
                        if (perimeters.find(length) != perimeters.end()) {
                            ++perimeters[length];
                        } else {
                            perimeters.insert(pair<int, int>(length, 1));
                        }
                        length += pivot;
                    }
                }
            }
        }

        int result = 0;
        for (pair<const int, int> p : perimeters) {
            if (1 == p.second) {
                ++result;
            }
        }
        cout << result << endl;
    }

private:
    bool is_relatively_prime(int i, int j) {
        while (i % j) {
            int auxiliary = i % j;
            i = j;
            j = auxiliary;
        }
        return 1 == j;
    }
};
