#include <iostream>
using namespace std;

class Problem028 {
public:
    void solution() {
        int target = 1001;
        int steps = target >> 1;
        long long result = (long long) (steps * steps * steps * 16 + steps * 26) / 3 + steps * steps * 10 + 1;
        cout << result << endl;
    }
};
