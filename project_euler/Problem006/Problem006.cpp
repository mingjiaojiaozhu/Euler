#include <iostream>
using namespace std;

class Problem006 {
public:
    void solution() {
        int target = 100;
        int result = target * (target - 1) * (target + 1) * (3 * target + 2) / 12;
        cout << result << endl;
    }
};
