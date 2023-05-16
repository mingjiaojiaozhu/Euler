#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *value;
    int length;
} Decimal;

static Decimal *create_array(void);
static void set_value(int value, Decimal *decimal);
static void get_summation(Decimal *decimal, Decimal *summation);
static void swap_decimal(Decimal *numerator, Decimal *denominator);
static int get_digits(int pivot);

void Problem057(void) {
    int target = 1000;
    Decimal *numerator = create_array();
    Decimal *denominator = create_array();
    set_value(3, numerator);
    set_value(2, denominator);

    int result = 0;
    for (int i = 2; i < target; ++i) {
        get_summation(denominator, numerator);
        get_summation(numerator, denominator);
        swap_decimal(numerator, denominator);
        if (numerator->length > denominator->length || get_digits(numerator->value[numerator->length - 1]) > get_digits(denominator->value[denominator->length - 1])) {
            ++result;
        }
    }
    printf("%d\n", result);
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

static void set_value(int value, Decimal *decimal) {
    decimal->value[0] = value;
    decimal->length = 1;
}

static void get_summation(Decimal *decimal, Decimal *summation) {
    for (int i = 0; i < decimal->length; ++i) {
        summation->value[i] += decimal->value[i];
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

static void swap_decimal(Decimal *numerator, Decimal *denominator) {
    int length = (numerator->length < denominator->length) ? denominator->length : numerator->length;
    for (int i = 0; i < length; ++i) {
        numerator->value[i] ^= denominator->value[i];
        denominator->value[i] ^= numerator->value[i];
        numerator->value[i] ^= denominator->value[i];
    }
    numerator->length ^= denominator->length;
    denominator->length ^= numerator->length;
    numerator->length ^= denominator->length;
}

static int get_digits(int value) {
    int result = 0;
    while (value) {
        ++result;
        value /= 10;
    }
    return result;
}
