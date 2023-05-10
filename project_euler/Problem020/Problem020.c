#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *value;
    int length;
} Decimal;

static void get_product(int value, Decimal *decimal);

void Problem020(void) {
    int target = 100;
    Decimal *decimal = (Decimal *) malloc(sizeof(Decimal));
    decimal->value = (int *) malloc(sizeof(int) * target);
    for (int i = 1; i < target; ++i) {
        decimal->value[i] = 0;
    }
    decimal->value[0] = target;
    decimal->length = 1;

    for (int i = target - 1; i > 1; --i) {
        get_product(i, decimal);
    }

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
