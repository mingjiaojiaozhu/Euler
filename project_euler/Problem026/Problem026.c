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
static int get_digit(int value, Array *remainders);
static void append(int value, Array *array);
static int find(int value, Array *array);

void Problem026(void) {
    int target = 1000;
    Array *remainders = (Array *) malloc(sizeof(Array));
    remainders->value = (int *) malloc(sizeof(int) * SIZE);
    remainders->length = 0;
    remainders->capacity = SIZE;

    int result = 0;
    int pivot = 0;
    for (int i = target - 1; i >= 7; i -= 2) {
        if (is_prime(i)) {
            int count = get_digit(i, remainders);
            if (pivot < count) {
                pivot = count;
                result = i;
            }
            if (count == i - 1) {
                break;
            }
        }
    }
    printf("%d\n", result);
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

static int get_digit(int value, Array *remainders) {
    remainders->length = 0;
    int remainder = 1;
    while (1) {
        append(remainder, remainders);
        remainder = remainder * 10 % value;
        int index = find(remainder, remainders);
        if (-1 != index) {
            return remainders->length - index;
        }
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

static int find(int value, Array *array) {
    for (int i = 0; i < array->length; ++i) {
        if (array->value[i] == value) {
            return i;
        }
    }
    return -1;
}
