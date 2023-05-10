#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static int is_pentagon(int value);
static void append(int value, Array *array);

void Problem044(void) {
    Array *pentagons = (Array *) malloc(sizeof(Array));
    pentagons->value = (int *) malloc(sizeof(int) * SIZE);
    pentagons->length = 0;
    pentagons->capacity = SIZE;
    int index = 1;
    while (1) {
        int current = index * (3 * index - 1) >> 1;
        for (int i = 0; i < pentagons->length; ++i) {
            int pentagon = pentagons->value[i];
            if (is_pentagon(current + pentagon) && is_pentagon(current - pentagon)) {
                printf("%d\n", current - pentagon);
                return;
            }
        }
        append(current, pentagons);
        ++index;
    }
}

static int is_pentagon(int value) {
    int delta = value * 24 + 1;
    return (fabs(floor(sqrt(delta) + 0.5) - sqrt(delta)) < 0.00000001 && !(((int) sqrt(delta) + 1) % 6)) ? 1 : 0;
}

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}
