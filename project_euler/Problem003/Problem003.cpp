#include <iostream>
using namespace std;

class Problem003 {
public:
    void solution() {
        long long target = 600851475143L;
        while (!(target & 1L)) {
            target >>= 1;
        }
        if (1L == target) {
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
