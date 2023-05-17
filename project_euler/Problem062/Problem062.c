#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_ARRAY 64
#define SIZE_MAP 256

typedef struct {
    long long *value;
    int length;
    int capacity;
} Array;

typedef struct node {
    int key;
    Array *value;
    struct node *next;
} Map;

static long long get_summation(long long value);
static void append_map(long long key, long long value, Map **map);
static void append_array(long long value, Array *array);

void Problem062(void) {
    int target = 5;
    Map **cubes = (Map **) malloc(sizeof(Map *) * SIZE_MAP);
    for (int i = 0; i < SIZE_MAP; ++i) {
        cubes[i] = NULL;
    }
    int index = 5;
    int pivot = 0;
    while (1) {
        long long value = (long long) pow(index, 3);
        long long summation = get_summation(value);
        int digit = (int) log10(value);
        if (pivot != digit) {
            for (int i = 0; i < SIZE_MAP; ++i) {
                cubes[i] = NULL;
            }
            pivot = digit;
        } else {
            Map *current = cubes[(int) (summation % SIZE_MAP)];
            while (current) {
                if (summation == current->key && current->value->length == target - 1) {
                    printf("%lld\n", current->value->value[0]);
                    return;
                }
                current = current->next;
            }
        }
        append_map(summation, value, cubes);
        ++index;
    }
}

static long long get_summation(long long value) {
    long long result = 0L;
    while (value) {
        result += (long long) pow(10, value % 10);
        value /= 10;
    }
    return result;
}

static void append_map(long long key, long long value, Map **map) {
    int index = (int) (key % SIZE_MAP);
    if (!map[index]) {
        map[index] = (Map *) malloc(sizeof(Map));
        map[index]->key = key;
        map[index]->value = (Array *) malloc(sizeof(Array));
        map[index]->value->value = (long long *) malloc(sizeof(long long) * SIZE_ARRAY);
        map[index]->value->length = 0;
        map[index]->value->capacity = SIZE_ARRAY;
        append_array(value, map[index]->value);
        map[index]->next = NULL;
        return;
    }

    Map *current = map[index];
    if (current->key == key) {
        append_array(value, current->value);
        return;
    }

    while (current->next) {
        current = current->next;
        if (current->key == key) {
            append_array(value, current->value);
            return;
        }
    }
    current->next = (Map *) malloc(sizeof(Map));
    current->next->key = key;
    current->next->value = (Array *) malloc(sizeof(Array));
    current->next->value->value = (long long *) malloc(sizeof(long long) * SIZE_ARRAY);
    current->next->value->length = 0;
    current->next->value->capacity = SIZE_ARRAY;
    append_array(value, current->next->value);
    current->next->next = NULL;
}

static void append_array(long long value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (long long *) realloc(array->value, sizeof(long long) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = value;
    ++array->length;
}
