#include <stdio.h>

void Problem003(void) {
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
    printf("%lld\n", target);
}
