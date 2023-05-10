#include <stdio.h>
#include <math.h>

static int is_prime(int value);
static int check_digit(int value, int *nexts, int *digits);

void Problem049(void) {
    int target = 3330;
    int other = 1487;
    int terms[2];
    int digits[10];
    for (int i = 10000 - (target << 1) - 1; i > 1000; i -= 2) {
        if (is_prime(i) && i != other) {
            terms[0] = i + target;
            terms[1] = terms[0] + target;
            if (is_prime(terms[0]) && is_prime(terms[1]) && check_digit(i, terms, digits)) {
                printf("%d%d%d\n", i, terms[0], terms[1]);
                return;
            }
        }
    }
}

static int is_prime(int value) {
    if (!(value & 1)) {
        return (2 == value) ? 1 : 0;
    }

    int border = (int) sqrt(value);
    for (int i = 3; i <= border; i += 2) {
        if (!(value % i)) {
            return 0;
        }
    }
    return (1 != value) ? 1 : 0;
}

static int check_digit(int value, int *terms, int *digits) {
    for (int i = 0; i < 10; ++i) {
        digits[i] = 0;
    }
    while (value) {
        digits[value % 10] = 1;
        value /= 10;
    }

    for (int i = 0; i < 2; ++i) {
        int term = terms[i];
        while (term) {
            if (!digits[term % 10]) {
                return 0;
            }
            term /= 10;
        }
    }
    return 1;
}
