#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int check_digits(int value);
static int is_truncatable(int value, int *primes);

void Problem037(void) {
    int target = 1000000;
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

    int result = 0;
    for (int i = 11; i < target; i += 2) {
        if (primes[i >> 1] && check_digits(i) && is_truncatable(i, primes)) {
            result += i;
        }
    }
    printf("%d\n", result);
}

static int check_digits(int value) {
    int remainder = value % 10;
    if (3 != remainder && 7 != remainder) {
        return 0;
    }

    value /= 10;
    while (value >= 10) {
        remainder = value % 10;
        if (1 != remainder && 3 != remainder && 7 != remainder && 9 != remainder) {
            return 0;
        }
        value /= 10;
    }
    return (2 == value || 3 == value || 5 == value || 7 == value) ? 1 : 0;
}

static int is_truncatable(int value, int *primes) {
    int divisor = 1;
    while (value / divisor >= 10) {
        divisor *= 10;
    }

    int head = value / 10;
    int tail = value % divisor;
    while (head && tail) {
        if ((2 != head && !primes[head >> 1]) || !primes[tail >> 1]) {
            return 0;
        }

        divisor /= 10;
        head /= 10;
        tail %= divisor;
    }
    return 1;
}
