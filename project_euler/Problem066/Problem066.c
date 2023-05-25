#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

typedef struct {
    int *value;
    int length;
} Decimal;

static int get_solution(int value, Array *factors, Decimal *previous, Decimal *current, Decimal *auxiliary);
static int is_greater(Decimal *current, Decimal *pivot);
static void swap_decimal(Decimal *previous, Decimal *current);
static int get_period(int value, Array *factors);
static void set_value(int value, Decimal *decimal);
static void get_convergents(Decimal *previous, Decimal *current, Array *factors);
static void get_product(Decimal *multiplicand, Decimal *multiplier, Decimal *product);
static void get_double(Decimal *decimal);
static void get_summation(Decimal *decimal, int factor, Decimal *summation);
static void carry(Decimal *decimal);
static void append(int value, Array *array);
static Decimal *create_array(void);

void Problem066(void) {
    int target = 1000;
    Array *factors = (Array *) malloc(sizeof(Array));
    factors->value = (int *) malloc(sizeof(int) * SIZE);
    factors->length = 0;
    factors->capacity = SIZE;
    Decimal *previous = create_array();
    Decimal *current = create_array();
    Decimal *auxiliary = create_array();

    int result = 0;
    Decimal *pivot = create_array();
    for (int i = 5; i <= target; ++i) {
        if (get_solution(i, factors, previous, current, auxiliary) && is_greater(current, pivot)) {
            swap_decimal(current, pivot);
            result = i;
        }
    }
    printf("%d\n", result);
}

static int get_solution(int value, Array *factors, Decimal *previous, Decimal *current, Decimal *auxiliary) {
    factors->length = 0;
    int start = get_period(value, factors);
    if (!start) {
        return 0;
    }

    set_value(0, previous);
    set_value(1, current);
    get_convergents(previous, current, factors);
    if (factors->length & 1) {
        return 1;
    }

    set_value(1, previous);
    set_value(start, auxiliary);
    get_convergents(previous, auxiliary, factors);
    swap_decimal(previous, current);
    get_product(previous, auxiliary, current);
    get_double(current);
    return 1;
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

static int get_period(int value, Array *factors) {
    if (fabs(floor(sqrt(value) + 0.5) - sqrt(value)) < 0.00000001) {
        return 0;
    }

    int initial = (int) sqrt(value);
    int pivot = initial << 1;
    int current = initial;
    int offset = 0;
    int factor = 1;
    while (current != pivot) {
        offset = current * factor - offset;
        factor = (value - offset * offset) / factor;
        current = (initial + offset) / factor;
        append(current, factors);
    }
    --factors->length;
    return initial;
}

static void set_value(int value, Decimal *decimal) {
    for (int i = 0; i < decimal->length; ++i) {
        decimal->value[i] = 0;
    }
    decimal->value[0] = value;
    decimal->length = 1;
}

static void get_convergents(Decimal *previous, Decimal *current, Array *factors) {
    for (int i = 0; i < factors->length; ++i) {
        get_summation(current, factors->value[i], previous);
        swap_decimal(previous, current);
    }
}

static void get_product(Decimal *multiplicand, Decimal *multiplier, Decimal *product) {
    for (int i = 0; i < multiplicand->length; ++i) {
        for (int j = 0; j < multiplier->length; ++j) {
            long long value = (long long) multiplicand->value[i] * multiplier->value[j];
            int index = i + j;
            product->value[index] += (int) (value % (int) 1e5);
            product->value[index + 1] += (int) (value / (int) 1e5);
        }
    }
    product->length = multiplicand->length + multiplier->length - 1;
    carry(product);
}

static void get_double(Decimal *decimal) {
    for (int i = 0; i < decimal->length; ++i) {
        decimal->value[i] <<= 1;
    }
    carry(decimal);
}

static void get_summation(Decimal *decimal, int factor, Decimal *summation) {
    for (int i = 0; i < decimal->length; ++i) {
        summation->value[i] += decimal->value[i] * factor;
    }
    carry(summation);
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

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
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
