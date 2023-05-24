#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static int get_next_prime(int value);
static int check_digits(int value, Array **digits);
static int check_prime_family(int pivot, int target, Array **digits, Array *steps, Array *auxiliary);
static int is_prime(int value);
static void combination(Array *digits, int start, int count, Array *steps, Array *auxiliary);
static Array *create_array(void);
static void append(int value, Array *array);

void Problem051(void) {
    int target = 8;
    Array **digits = (Array **) malloc(sizeof(Array *) * 3);
    for (int i = 0; i < 3; ++i) {
        digits[i] = create_array();
    }
    Array *steps = create_array();
    Array *auxiliary = create_array();

    int index = 1111;
    while (1) {
        int prime = get_next_prime(index);
        if (check_digits(prime, digits) && check_prime_family(prime, target, digits, steps, auxiliary)) {
            printf("%d\n", prime);
            return;
        }
        index = prime + 1;
    }
}

static int get_next_prime(int value) {
    if (!(value & 1)) {
        ++value;
    }

    while (!is_prime(value)) {
        value += 2;
    }
    return value;
}

static int check_digits(int value, Array **digits) {
    for (int i = 0; i < 3; ++i) {
        digits[i]->length = 0;
    }

    value /= 10;
    int count = 1;
    while (value) {
        int remainder = value % 10;
        if (!remainder || 1 == remainder || 2 == remainder) {
            append(count, digits[remainder]);
        }
        value /= 10;
        ++count;
    }

    for (int i = 0; i < 3; ++i) {
        if (digits[i]->length >= 3) {
            return 1;
        }
    }
    return 0;
}

static int check_prime_family(int pivot, int target, Array **digits, Array *steps, Array *auxiliary) {
    int is_family = 0;
    for (int i = 0; i < 3; ++i) {
        if (digits[i]->length < 3) {
            continue;
        }

        steps->length = 0;
        auxiliary->length = 0;
        combination(digits[i], 0, 3, steps, auxiliary);
        for (int j = 0; j < steps->length; ++j) {
            int count = 10 - target - i;
            int value = pivot;
            for (int k = i; k < 9; ++k) {
                value += steps->value[j];
                if (!is_prime(value)) {
                    --count;
                }
                if (count < 0) {
                    break;
                }
            }
            is_family = !count;
        }
    }
    return is_family;
}

static int is_prime(int value) {
    if (1 != value % 6 && 5 != value % 6) {
        return (2 == value || 3 == value) ? 1 : 0;
    }

    int border = (int) sqrt(value);
    for (int i = 5; i <= border; i += 6) {
        if (!(value % i) || !(value % (i + 2))) {
            return 0;
        }
    }
    return (1 != value) ? 1 : 0;
}

static void combination(Array *digits, int start, int count, Array *steps, Array *auxiliary) {
    if (count == auxiliary->length) {
        int value = 0;
        for (int i = 0; i < auxiliary->length; ++i) {
            value += auxiliary->value[i];
        }
        append(value, steps);
        return;
    }

    for (int i = start; i < digits->length; ++i) {
        append((int) pow(10, digits->value[i]), auxiliary);
        combination(digits, i + 1, count, steps, auxiliary);
        --auxiliary->length;
    }
}

static Array *create_array(void) {
    Array *array = (Array *) malloc(sizeof(Array));
    array->value = (int *) malloc(sizeof(int) * SIZE);
    array->length = 0;
    array->capacity = SIZE;
    return array;
}

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}
