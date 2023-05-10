#include <stdio.h>

static int common_divisor(int i, int j);

void Problem033(void) {
    int numerator = 1;
    int denominator = 1;
    for (int i = 1; i < 10; ++i) {
        for (int j = i + 1; j < 10; ++j) {
            if (!((9 * i * j) % (10 * i - j)) && (9 * i * j) / (10 * i - j) < 10) {
                numerator *= i;
                denominator *= j;
            }
        }
    }
    printf("%d\n", denominator / common_divisor(denominator, numerator));
}

static int common_divisor(int i, int j) {
    while (i % j) {
        int auxiliary = i % j;
        i = j;
        j = auxiliary;
    }
    return j;
}
