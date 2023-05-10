#include <stdio.h>

static int is_pandigital(int value, int *digits);

void Problem038(void) {
    int digits[9];
    for (int i = 9487; i >= 9234; --i) {
        for (int j = 0; j < 9; ++j) {
            digits[j] = 0;
        }

        if (is_pandigital(i, digits) && is_pandigital(i << 1, digits)) {
            printf("%d%d\n", i, i << 1);
            return;
        }
    }
}

static int is_pandigital(int value, int *digits) {
    while (value) {
        int index = value % 10 - 1;
        if (index < 0 || digits[index]) {
            return 0;
        }
        digits[index] = 1;
        value /= 10;
    }
    return 1;
}
