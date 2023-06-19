#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int *value;
    int length;
} Decimal;

static int is_lychrel(int value, Decimal *decimal, int *auxiliary);
static void set_value(int value, Decimal *decimal);
static void reverse_value(Decimal *decimal, int *auxiliary);
static void get_summation(Decimal *decimal, int *auxiliary);
static int is_equal(Decimal *decimal, int *auxiliary);

void Problem055(void) {
    int target = 10000;
    Decimal *decimal = (Decimal *) malloc(sizeof(Decimal));
    decimal->value = (int *) malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; ++i) {
        decimal->value[i] = 0;
    }
    decimal->length = 0;
    int auxiliary[100];
    int result = 0;
    for (int i = 1; i < target; ++i) {
        if (is_lychrel(i, decimal, auxiliary)) {
            ++result;
        }
    }
    printf("%d\n", result);
}

static int is_lychrel(int value, Decimal *decimal, int *auxiliary) {
    set_value(value, decimal);
    reverse_value(decimal, auxiliary);
    get_summation(decimal, auxiliary);

    int count = 0;
    while (count < 50) {
        reverse_value(decimal, auxiliary);
        if (is_equal(decimal, auxiliary)) {
            return 0;
        }
        get_summation(decimal, auxiliary);
        ++count;
    }
    return 1;
}

static void set_value(int value, Decimal *decimal) {
    for (int i = 0; i < 100; ++i) {
        decimal->value[i] = 0;
    }
    decimal->length = 0;
    while (value) {
        decimal->value[decimal->length] = value % (int) 1e5;
        ++decimal->length;
        value /= (int) 1e5;
    }
}

static void reverse_value(Decimal *decimal, int *auxiliary) {
    for (int i = 0; i < 100; ++i) {
        auxiliary[i] = 0;
    }

    int index = 0;
    int count = 0;
    for (int i = decimal->length - 1; i >= 0; --i) {
        int value = decimal->value[i];
        int divisor = (int) 1e5 / 10;
        if (i == decimal->length - 1) {
            while (!(value / divisor)) {
                divisor /= 10;
            }
        }
        while (divisor) {
            auxiliary[index] += (value / divisor) * (int) pow(10, count);
            value %= divisor;
            divisor /= 10;
            ++count;
            if (5 == count) {
                ++index;
                count = 0;
            }
        }
    }
}

static void get_summation(Decimal *decimal, int *auxiliary) {
    for (int i = 0; i < decimal->length; ++i) {
        decimal->value[i] += auxiliary[i];
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

static int is_equal(Decimal *decimal, int *auxiliary) {
    for (int i = 0; i < decimal->length; ++i) {
        if (decimal->value[i] != auxiliary[i]) {
            return 0;
        }
    }
    return 1;
}
