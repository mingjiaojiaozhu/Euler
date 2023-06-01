#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static int get_ways(int target, Array *primes);
static int is_prime(int value);
static void append(int value, Array *array);

void Problem077(void) {
    int target = 5000;
    Array *primes = (Array *) malloc(sizeof(Array));
    primes->value = (int *) malloc(sizeof(int) * SIZE);
    primes->length = 0;
    primes->capacity = SIZE;
    append(2, primes);
    append(3, primes);
    int result = 11;
    while (get_ways(result, primes) <= target) {
        ++result;
    }
    printf("%d\n", result);
}

static int get_ways(int target, Array *primes) {
    int index = primes->value[primes->length - 1] + 2;
    while (index <= target) {
        if (is_prime(index)) {
            append(index, primes);
        }
        index += 2;
    }

    int *ways = (int *) malloc(sizeof(int) * (target + 1));
    for (int i = 1; i <= target; ++i) {
        ways[i] = 0;
    }
    ways[0] = 1;
    for (int i = 0; i < primes->length; ++i) {
        int prime = primes->value[i];
        for (int j = prime; j <= target; ++j) {
            ways[j] += ways[j - prime];
        }
    }
    return ways[target];
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
