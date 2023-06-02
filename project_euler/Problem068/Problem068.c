#include <stdio.h>
#include <stdlib.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static void append(int value, Array *array);

void Problem068(void) {
    int target = 10;
    int border = target >> 1;
    int start = border + 1;
    int summation = ((target * (target + 1) >> 1) + (border * (border + 1) >> 1)) / border;
    int pivot = summation - border - start;

    Array *ring = (Array *) malloc(sizeof(Array));
    ring->value = (int *) malloc(sizeof(int) * SIZE);
    ring->length = 0;
    ring->capacity = SIZE;
    append(start, ring);
    append(border, ring);
    append(pivot, ring);
    for (int i = target; i > start; --i) {
        append(i, ring);
        append(pivot, ring);
        pivot = summation - pivot - i;
        append(pivot, ring);
    }

    long long result = 0L;
    for (int i = 0; i < ring->length; ++i) {
        int value = ring->value[i];
        if (value >= 10) {
            result = result * 100 + value;
        } else {
            result = result * 10 + value;
        }
    }
    printf("%lld\n", result);
}

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}
