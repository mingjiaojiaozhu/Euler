#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *value;
    int length;
} Decimal;

static void set_value(int value, Decimal *decimal);
static void get_summation(Decimal *decimal, int factor, Decimal *summation);
static void swap_decimal(Decimal *previous, Decimal *current);
static Decimal *create_array(void);

void Problem065(void) {
    int target = 100;
    Decimal *previous = create_array();
    Decimal *current = create_array();
    set_value(1, previous);
    set_value(2, current);
    for (int i = 2; i <= target; ++i) {
        int factor = 1;
        if (!(i % 3)) {
            factor = (i << 1) / 3;
        }
        get_summation(current, factor, previous);
        swap_decimal(previous, current);
    }

    int result = 0;
    for (int i = 0; i < current->length; ++i) {
        int value = current->value[i];
        while (value) {
            result += value % 10;
            value /= 10;
        }
    }
    printf("%d\n", result);
}

static void set_value(int value, Decimal *decimal) {
    decimal->value[0] = value;
    decimal->length = 1;
}

static void get_summation(Decimal *decimal, int factor, Decimal *summation) {
    for (int i = 0; i < decimal->length; ++i) {
        summation->value[i] += decimal->value[i] * factor;
    }

    for (int i = 0; i < summation->length; ++i) {
        if (summation->value[i] >= (int) 1e5) {
            summation->value[i + 1] += summation->value[i] / (int) 1e5;
            summation->value[i] %= (int) 1e5;
        }
    }
    if (summation->value[summation->length]) {
        ++summation->length;
    }
}

static void swap_decimal(Decimal *previous, Decimal *current) {
    int length = (previous->length < current->length) ? current->length : previous->length;
    for (int i = 0; i < length; ++i) {
        previous->value[i] ^= current->value[i];
        current->value[i] ^= previous->value[i];
        previous->value[i] ^= current->value[i];
    }
    previous->length ^= current->length;
    current->length ^= previous->length;
    previous->length ^= current->length;
}

static Decimal *create_array(void) {
    Decimal *decimal = (Decimal *) malloc(sizeof(Decimal));
    decimal->value = (int *) malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; ++i) {
        decimal->value[i] = 0;
    }
    decimal->length = 0;
    return decimal;
}
