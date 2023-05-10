#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void get_divisor_summation(int value, int *divisors, int length);
static int is_relatively_prime(int i, int j);

void Problem021(void) {
    int target = 10000;
    int *divisors = (int *) malloc(sizeof(int) * target);
    for (int i = 0; i < target; ++i) {
        divisors[i] = -1;
    }
    for (int i = 2; i <= target; ++i) {
        get_divisor_summation(i, divisors, target);
    }
    for (int i = 1; i < target; ++i) {
        divisors[i] -= i + 1;
    }

    int result = 0;
    for (int i = 2; i <= target; ++i) {
        int divisor = divisors[i - 1];
        if (divisor > i && divisor <= target && divisors[divisor - 1] == i) {
            result += i + divisor;
        }
    }
    printf("%d\n", result);
}

static void get_divisor_summation(int value, int *divisors, int length) {
    if (-1 == divisors[value - 1]) {
        int index = value;
        int count = 1;
        while (index <= length) {
            divisors[index - 1] = ((int) pow(value, count + 1) - 1) / (value - 1);
            index *= value;
            ++count;
        }

        for (int i = (value - 1 < length / value) ? value - 1 : length / value; i >= 2; --i) {
            divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1];
        }
    } else {
        for (int i = (value - 1 < length / value) ? value - 1 : length / value; i >= 2; --i) {
            if (is_relatively_prime(value, i) && -1 == divisors[value * i - 1]) {
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1];
            }
        }
    }
}

static int is_relatively_prime(int i, int j) {
    while (i % j) {
        int auxiliary = i % j;
        i = j;
        j = auxiliary;
    }
    return (1 == j) ? 1 : 0;
}
