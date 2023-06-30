#include <stdio.h>

void Problem100(void) {
    long long target = 1000000000000L;
    long long index = 1L;
    long long result = 1L;
    while (index < target) {
        long long auxiliary = (index << 1) + result * 3 - 2;
        index = index * 3 + (result << 2) - 3;
        result = auxiliary;
    }
    printf("%lld\n", result);
}
