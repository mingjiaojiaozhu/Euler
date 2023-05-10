#include <iostream>
using namespace std;

class Problem015 {
public:
    void solution() {
        int target = 20;
        int border = target << 1;
        long long result = 1L;
        for (int i = border - 1; i > target; i -= 2) {
            result = (result << 1) * i / ((border - i + 1) >> 1);
        }
        cout << result << endl;
    }
};
