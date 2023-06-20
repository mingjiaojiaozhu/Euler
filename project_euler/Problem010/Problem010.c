#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Problem010(void) {
    int target = 2000000;
    int length = (target + 1) >> 1;
    int *primes = (int *) malloc(sizeof(int) * length);
    primes[0] = 0;
    for (int i = 1; i < length; ++i) {
        primes[i] = 1;
    }

    int border = (int) sqrt(target);
    for (int i = 3; i <= border; i += 2) {
        if (primes[i >> 1]) {
            for (int j = i * i >> 1; j < length; j += i) {
                primes[j] = 0;
            }
        }
    }

    long long result = 2L;
    for (int i = 1; i < length; ++i) {
        if (primes[i]) {
            result += (i << 1) + 1;
        }
    }
    printf("%lld\n", result);
}
