#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int *value;
    int length;
} Decimal;

static void get_power(int value, Decimal *decimal, int *auxiliary, int length);
static void get_square(Decimal *decimal, int *auxiliary, int length);
static void get_double(Decimal *decimal);

void Problem016(void) {
    int target = 1000;
    int length = (target + 4) / 5;
    Decimal *decimal = (Decimal *) malloc(sizeof(Decimal));
    decimal->value = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        decimal->value[i] = 0;
    }
    decimal->length = 0;
    int *auxiliary = (int *) malloc(sizeof(int) * length);
    get_power(target, decimal, auxiliary, length);

    int result = 0;
    for (int i = 0; i < decimal->length; ++i) {
        int value = decimal->value[i];
        while (value > 0) {
            result += value % 10;
            value /= 10;
        }
    }
    printf("%d\n", result);
}

static void get_power(int value, Decimal *decimal, int *auxiliary, int length) {
    if (value < 8) {
        decimal->value[0] = (int) pow(2, value);
        decimal->length = 1;
        return;
    }

    get_power(value >> 1, decimal, auxiliary, length);
    get_square(decimal, auxiliary, length);
    if (value & 1) {
        get_double(decimal);
    }
}

static void get_square(Decimal *decimal, int *auxiliary, int length) {
    for (int i = 0; i < length; ++i) {
        auxiliary[i] = 0;
    }
    for (int i = 0; i < decimal->length; ++i) {
        for (int j = 0; j < decimal->length; ++j) {
            long long result = (long long) decimal->value[i] * decimal->value[j];
            int index = i + j;
            auxiliary[index] += (int) (result % (int) 1e5);
            auxiliary[index + 1] += (int) (result / (int) 1e5);
        }
    }

    decimal->length = (decimal->length << 1) - 1;
    for (int i = 0; i < decimal->length; ++i) {
        if (auxiliary[i] >= (int) 1e5) {
            auxiliary[i + 1] += auxiliary[i] / (int) 1e5;
            auxiliary[i] %= (int) 1e5;
        }
    }
    if (auxiliary[decimal->length]) {
        ++decimal->length;
    }
    memcpy(decimal->value, auxiliary, sizeof(int) * decimal->length);
}

static void get_double(Decimal *decimal) {
    for (int i = 0; i < decimal->length; ++i) {
        decimal->value[i] <<= 1;
    }

    for (int i = 0; i < decimal->length; ++i) {
        if (decimal->value[i] >= (int) 1e5) {
            decimal->value[i + 1] += decimal->value[i] / (int) 1e5;
            decimal->value[i] %= (int) 1e5;
        }
    }
    if (decimal->value[decimal->length]) {
        ++decimal->length;
    }
}
