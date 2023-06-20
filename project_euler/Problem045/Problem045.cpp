#include <iostream>
#include <cmath>
using namespace std;

class Problem045 {
public:
    void solution() {
        long long index = 144L;
        while (true) {
            long long hexagon = index * ((index << 1) - 1);
            if (is_pentagon(hexagon)) {
                cout << hexagon << endl;
                return;
            }
            ++index;
        }
    }

private:
    bool is_pentagon(long long value) {
        double auxiliary = sqrt(value * 24 + 1);
        return fabs(floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && !(((long long) auxiliary + 1) % 6);
    }
};
