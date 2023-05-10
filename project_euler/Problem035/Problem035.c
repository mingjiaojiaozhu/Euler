#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int check_digits(int value);
static int is_circular(int value, int *primes);

void Problem035(void) {
    int target = 1000000;
    int length = (target + 1) >> 1;
    int *primes = (int *) malloc(sizeof(int) * length);
    primes[0] = 0;
    for (int i = 1; i < length; ++i) {
        primes[i] = 1;
    }

    int border = (int) sqrt(target) + 1;
    for (int i = 3; i <= border; i += 2) {
        if (primes[i >> 1]) {
            for (int j = i * i >> 1; j < length; j += i) {
                primes[j] = 0;
            }
        }
    }

    int result = 13;
    for (int i = 101; i < target; i += 2) {
        if (primes[i >> 1] && check_digits(i) && is_circular(i, primes)) {
            ++result;
        }
    }
    printf("%d\n", result);
}

static int check_digits(int value) {
    while (value) {
        int remainder = value % 10;
        if (1 != remainder && 3 != remainder && 7 != remainder && 9 != remainder) {
            return 0;
        }
        value /= 10;
    }
    return 1;
}

static int is_circular(int value, int *primes) {
    int divisor = 1;
    int length = 1;
    while (value / divisor >= 10) {
        divisor *= 10;
        ++length;
    }

    for (int i = 1; i < length; ++i) {
        value = (value % 10) * divisor + value / 10;
        if (!primes[value >> 1]) {
            return 0;
        }
    }
    return 1;
}
