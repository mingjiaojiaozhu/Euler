#include <stdio.h>
#include <stdlib.h>

static int get_factors(int value, int *factors, int length);
static int is_relatively_prime(int i, int j);
static int minimum(int i, int j);

void Problem047(void) {
    int target = 4;
    int length = 200000;
    int *factors = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        factors[i] = -1;
    }

    int count = 0;
    for (int i = 2; i <= length; ++i) {
        if (target == get_factors(i, factors, length)) {
            ++count;
            if (target == count) {
                printf("%d\n", i - 3);
                return;
            }
        } else {
            count = 0;
        }
    }
}

static int get_factors(int value, int *factors, int length) {
    if (-1 == factors[value - 1]) {
        long long index = value;
        while (index <= length) {
            factors[(int) index - 1] = 1;
            index *= value;
        }

        for (int i = minimum(value - 1, length / value); i >= 2; --i) {
            factors[value * i - 1] = factors[value - 1] + factors[i - 1];
        }
    } else {
        for (int i = minimum(value - 1, length / value); i >= 2; --i) {
            if (is_relatively_prime(value, i) && -1 == factors[value * i - 1]) {
                factors[value * i - 1] = factors[value - 1] + factors[i - 1];
            }
        }
    }
    return factors[value - 1];
}

static int is_relatively_prime(int i, int j) {
    while (i % j) {
        int auxiliary = i % j;
        i = j;
        j = auxiliary;
    }
    return (1 == j) ? 1 : 0;
}

static int minimum(int i, int j) {
    return (i < j) ? i : j;
}
