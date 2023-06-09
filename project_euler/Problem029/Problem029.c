#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    double *value;
    int length;
    int capacity;
} Array;

static void append(double value, Array *array);
static int compare(const void *p, const void *q);

void Problem029(void) {
    int start = 2;
    int end = 100;
    Array *terms = (Array *) malloc(sizeof(Array));
    terms->value = (double *) malloc(sizeof(double) * SIZE);
    terms->length = 0;
    terms->capacity = SIZE;

    for (int i = start; i <= end; ++i) {
        for (int j = start; j <= end; ++j) {
            append(i * log(j), terms);
        }
    }

    qsort(terms->value, terms->length, sizeof(double), compare);

    int result = terms->length;
    for (int i = result - 1; i >= 1; --i) {
        if (fabs(terms->value[i] - terms->value[i - 1]) < 0.00000001) {
            --result;
        }
    }
    printf("%d\n", result);
}

static void append(double value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (double *) realloc(array->value, sizeof(double) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}

static int compare(const void *p, const void *q) {
    return (*(double *) p > *(double *) q) ? 1 : -1;
}
