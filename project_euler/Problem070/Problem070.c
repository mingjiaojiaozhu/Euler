#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static int get_previous_prime(int value);
static int get_next_prime(int value);
static void get_digits(int value, int *digits);
static int check_digits(int *pivots, int *digits);
static int is_prime(int value);
static void append(int value, Array *array);

void Problem070(void) {
    int target = 10000000;
    int pivot = (int) sqrt(target);
    int start = get_previous_prime(pivot);
    int end = get_next_prime(pivot);
    Array *primes = (Array *) malloc(sizeof(Array));
    primes->value = (int *) malloc(sizeof(int) * SIZE);
    primes->length = 0;
    primes->capacity = SIZE;
    append(end, primes);
    int pivots[10];
    int digits[10];
    int result = 0;
    while (1) {
        for (int i = 0; i < primes->length; ++i) {
            int prime = primes->value[i];
            get_digits(start * prime, pivots);
            get_digits((start - 1) * (prime - 1), digits);
            if (check_digits(pivots, digits)) {
                result = start * prime;
            }
        }

        end = get_next_prime(primes->value[primes->length - 1]);
        while (start * end < target) {
            append(end, primes);
            get_digits(start * end, pivots);
            get_digits((start - 1) * (end - 1), digits);
            if (check_digits(pivots, digits)) {
                result = start * end;
            }
            end = get_next_prime(end);
        }

        if (0 != result) {
            printf("%d\n", result);
            return;
        }
        start = get_previous_prime(start);
    }
}

static int get_previous_prime(int value) {
    if (!(value & 1)) {
        --value;
    } else {
        value -= 2;
    }

    while (!is_prime(value)) {
        value -= 2;
    }
    return value;
}

static int get_next_prime(int value) {
    if (!(value & 1)) {
        ++value;
    } else {
        value += 2;
    }

    while (!is_prime(value)) {
        value += 2;
    }
    return value;
}

static void get_digits(int value, int *digits) {
    for (int i = 0; i < 10; ++i) {
        digits[i] = 0;
    }

    while (value) {
        ++digits[value % 10];
        value /= 10;
    }
}

static int check_digits(int *pivots, int *digits) {
    for (int i = 0; i < 10; ++i) {
        if (pivots[i] != digits[i]) {
            return 0;
        }
    }
    return 1;
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

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}
