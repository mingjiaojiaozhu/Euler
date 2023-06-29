#include <iostream>
using namespace std;

class Problem003 {
public:
    void solution() {
        long long target = 600851475143L;
        while (!(target & 1)) {
            target >>= 1;
        }
        if (1 == target) {
            target = 2L;
        }

        long long factor = 3L;
        while (factor < target) {
            while (!(target % factor) && target != factor) {
                target /= factor;
            }
            factor += 2L;
        }
        cout << target << endl;
    }
};
