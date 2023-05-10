#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static int get_champernowne(int value, Array *borders);
static int get_index(int value, Array *borders);
static void append(int value, Array *array);

void Problem040(void) {
    int target = 1000000;
    Array *borders = (Array *) malloc(sizeof(Array));
    borders->value = (int *) malloc(sizeof(int) * SIZE);
    borders->length = 0;
    borders->capacity = SIZE;

    int index = 0;
    while (1) {
        int value = ((int) pow(10, index) * (9 * index - 1) + 1) / 9;
        append(value, borders);
        if (value > target) {
            break;
        }
        ++index;
    }

    int result = 1;
    while (target) {
        result *= get_champernowne(target, borders);
        target /= 10;
    }
    printf("%d\n", result);
}

static int get_champernowne(int value, Array *borders) {
    int index = get_index(value, borders) - 1;
    value -= borders->value[index] + 1;
    int digit = (int) pow(10, index) + value / (index + 1);
    for (int i = value % (index + 1); i < index; ++i) {
        digit /= 10;
    }
    return digit % 10;
}

static int get_index(int value, Array *borders) {
    int start = 0;
    int end = borders->length - 1;
    while (start <= end) {
        int current = start + ((end - start) >> 1);
        if (borders->value[current] <= value) {
            start = current + 1;
        } else {
            end = current - 1;
        }
    }
    return start;
}

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}
