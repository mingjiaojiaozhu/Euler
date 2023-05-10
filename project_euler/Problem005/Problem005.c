#include <stdio.h>
#include <stdlib.h>

static void factorize(int value, int *powers);

void Problem005(void) {
    int target = 20;
    int *powers = (int *) malloc(sizeof(int) * target);
    for (int i = 0; i < target; ++i) {
        powers[i] = 0;
    }
    for (int i = 2; i <= target; ++i) {
        factorize(i, powers);
    }

    long long result = 1L;
    for (int i = 1; i < target; ++i) {
        for (int j = 0; j < powers[i]; ++j) {
            result *= i + 1;
        }
    }
    printf("%lld\n", result);
}

static void factorize(int value, int *powers) {
    int power = 0;
    while (!(value & 1)) {
        value >>= 1;
        ++power;
    }
    if (powers[1] < power) {
        powers[1] = power;
    }

    int factor = 3;
    while (factor <= value) {
        power = 0;
        while (!(value % factor)) {
            value /= factor;
            ++power;
        }
        if (powers[factor - 1] < power) {
            powers[factor - 1] = power;
        }
        factor += 2;
    }
}
