#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int *value;
    int length;
} Decimal;

static void get_digits(int value, Decimal *current, Decimal *auxiliary, int length, int pivot);
static int get_summation(Decimal *current);
static void set_value(int value, Decimal *decimal);
static int check_length(Decimal *current, int length, int pivot);
static int is_greater(Decimal *current, Decimal *pivot);
static void get_difference(Decimal *decimal, Decimal *difference);
static void get_product(Decimal *decimal, int factor);
static void fill_zero(Decimal *decimal);
static void carry(Decimal *decimal);
static int add_digit(int value);
static Decimal *create_array(void);

void Problem080(void) {
    int target = 100;
    Decimal *current = create_array();
    Decimal *auxiliary = create_array();
    int length = (target + 2) / 5 + 1;
    int pivot = (int) pow(10, (target + 2) % 5);
    int result = 0;
    for (int i = 2; i <= target; ++i) {
        double root = sqrt(i);
        if (fabs(floor(root + 0.5) - root) > 0.00000001) {
            get_digits(i, current, auxiliary, length, pivot);
            result += get_summation(current);
        }
    }
    printf("%d\n", result);
}

static void get_digits(int value, Decimal *current, Decimal *auxiliary, int length, int pivot) {
    set_value(5, current);
    set_value(value * 5, auxiliary);
    while (check_length(current, length, pivot)) {
        if (!is_greater(current, auxiliary)) {
            get_difference(current, auxiliary);
            current->value[0] += 10;
            carry(current);
        } else {
            get_product(auxiliary, 100);
            fill_zero(current);
        }
    }
}

static int get_summation(Decimal *current) {
    int result = add_digit(current->value[0] / (int) 1e3);
    for (int i = 1; i < current->length; i++) {
        result += add_digit(current->value[i]);
    }
    return result;
}

static void set_value(int value, Decimal *decimal) {
    for (int i = 0; i < decimal->length; ++i) {
        decimal->value[i] = 0;
    }
    decimal->value[0] = value;
    decimal->length = 1;
}

static int check_length(Decimal *current, int length, int pivot) {
    if (current->length < length) {
        return 1;
    }
    return (current->value[length - 1] < pivot) ? 1 : 0;
}

static int is_greater(Decimal *current, Decimal *pivot) {
    if (current->length != pivot->length) {
        return (current->length > pivot->length) ? 1 : 0;
    }

    for (int i = current->length - 1; i >= 0; --i) {
        if (current->value[i] != pivot->value[i]) {
            return (current->value[i] > pivot->value[i]) ? 1 : 0;
        }
    }
    return 0;
}

static void get_difference(Decimal *decimal, Decimal *difference) {
    for (int i = 0; i < decimal->length; ++i) {
        difference->value[i] -= decimal->value[i];
    }

    for (int i = 0; i < difference->length; ++i) {
        if (difference->value[i] < 0) {
            --difference->value[i + 1];
            difference->value[i] += (int) 1e5;
        }
    }
    while (!difference->value[difference->length - 1]) {
        --difference->length;
    }
}

static void get_product(Decimal *decimal, int factor) {
    for (int i = 0; i < decimal->length; ++i) {
        decimal->value[i] *= factor;
    }
    carry(decimal);
}

static void fill_zero(Decimal *decimal) {
    int remainder = decimal->value[0] % 10;
    decimal->value[0] -= remainder;
    get_product(decimal, 10);
    decimal->value[0] += remainder;
}

static void carry(Decimal *decimal) {
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

static int add_digit(int value) {
    int result = 0;
    while (value) {
        result += value % 10;
        value /= 10;
    }
    return result;
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
