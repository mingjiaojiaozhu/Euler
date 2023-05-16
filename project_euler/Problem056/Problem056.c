#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *value;
    int length;
} Decimal;

static void set_value(int value, Decimal *decimal);
static void get_product(int value, Decimal *decimal);
static int get_digital(Decimal *decimal, int pivot);

void Problem056(void) {
    int target = 100;
    Decimal *decimal = (Decimal *) malloc(sizeof(Decimal));
    decimal->value = (int *) malloc(sizeof(int) * target);
    for (int i = 0; i < target; ++i) {
        decimal->value[i] = 0;
    }
    decimal->length = 0;

    int result = 0;
    for (int i = 2; i < target; ++i) {
        for (int j = 0; j < target; ++j) {
            decimal->value[j] = 0;
        }
        set_value(i, decimal);
        for (int j = 2; j < target; ++j) {
            get_product(i, decimal);
            result = get_digital(decimal, result);
        }
    }
    printf("%d\n", result);
}

static void set_value(int value, Decimal *decimal) {
    decimal->value[0] = value;
    decimal->length = 1;
}

static void get_product(int value, Decimal *decimal) {
    for (int i = 0; i < decimal->length; ++i) {
        decimal->value[i] *= value;
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

static int get_digital(Decimal *decimal, int pivot) {
    int result = 0;
    for (int i = 0; i < decimal->length; ++i) {
        int value = decimal->value[i];
        while (value) {
            result += value % 10;
            value /= 10;
        }
    }
    return (result < pivot) ? pivot : result;
}
