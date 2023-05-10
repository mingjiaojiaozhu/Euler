#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int *value;
    int length;
} Array;

static int is_prime(int value);
static int get_digit(int value, Array *remainders);
static void append(int value, Array *array);
static int find(int value, Array *array);

void Problem026(void) {
    int target = 1000;
    Array *remainders = (Array *) malloc(sizeof(Array));
    remainders->value = (int *) malloc(sizeof(int) * target);
    remainders->length = 0;

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
    if (!(value & 1)) {
        return (2 == value) ? 1 : 0;
    }

    int border = (int) sqrt(value);
    for (int i = 3; i <= border; i += 2) {
        if (!(value % i)) {
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
