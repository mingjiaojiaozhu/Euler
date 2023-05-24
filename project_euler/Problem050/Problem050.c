#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static int is_prime(int value);
static void append(int value, Array *array);

void Problem050(void) {
    int target = 1000000;
    Array *primes = (Array *) malloc(sizeof(Array));
    primes->value = (int *) malloc(sizeof(int) * SIZE);
    primes->length = 0;
    primes->capacity = SIZE;
    append(2, primes);

    int index = 3;
    int summation = 2;
    while (summation < target) {
        if (is_prime(index)) {
            append(index, primes);
            summation += index;
        }
        index += 2;
    }

    for (int i = primes->length - 1; i > 0; --i) {
        int value = summation - primes->value[i];
        if (is_prime(value)) {
            printf("%d\n", value);
            return;
        }
        summation = value;

        for (int j = i; j < primes->length; ++j) {
            value += primes->value[j] - primes->value[j - i];
            if (is_prime(value) && value < target) {
                printf("%d\n", value);
                return;
            }
        }
    }
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
