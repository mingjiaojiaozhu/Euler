#include <iostream>
#include <cmath>
using namespace std;

class Problem045 {
public:
    void solution() {
        long long index = 144;
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
        long long delta = value * 24 + 1;
        return fabs(floor(sqrt(delta) + 0.5) - sqrt(delta)) < 0.00000001 && !(((long long) sqrt(delta) + 1) % 6);
    }
};
