#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10
#define SIZE_ARRAY 64
#define SIZE_SET 256

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

typedef struct {
    int **value;
    int length;
    int capacity;
} Array_list;

typedef struct node {
    int value;
    struct node *next;
} Set;

static void combination(int *elements, int index, int count, Array_list *ways, int *auxiliary, int size);
static int reverse_9_to_6(int value);
static int check_digits(Array_list *ways, int i, int j, Array *squares, Set **arrangements, int size);
static void append_array(int value, Array *array);
static void append_array_list(int *value, Array_list *array, int size);
static void append_set(int value, Set **set);
static int contains(int value, Set **set);

void Problem090(void) {
    int elements[LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 6};
    Array_list *ways = (Array_list *) malloc(sizeof(Array_list));
    ways->value = (int **) malloc(sizeof(int *) * SIZE_ARRAY);
    ways->length = 0;
    ways->capacity = SIZE_ARRAY;
    int auxiliary[6];
    combination(elements, 0, 6, ways, auxiliary, 0);

    Array *squares = (Array *) malloc(sizeof(Array));
    squares->value = (int *) malloc(sizeof(int) * SIZE_ARRAY);
    squares->length = 0;
    squares->capacity = SIZE_ARRAY;
    for (int i = 1; i < 10; ++i) {
        append_array(reverse_9_to_6(i * i), squares);
    }

    int result = 0;
    Set **arrangements = (Set **) malloc(sizeof(Set *) * SIZE_SET);
    for (int i = 0; i < SIZE_SET; ++i) {
        arrangements[i] = NULL;
    }
    for (int i = 0; i < ways->length; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (check_digits(ways, i, j, squares, arrangements, 6)) {
                ++result;
            }
        }
    }
    printf("%d\n", result);
}

static void combination(int *elements, int index, int count, Array_list *ways, int *auxiliary, int size) {
    if (count == size) {
        append_array_list(auxiliary, ways, count);
        return;
    }

    for (int i = index; i < LENGTH; ++i) {
        auxiliary[size] = elements[i];
        ++size;
        combination(elements, i + 1, count, ways, auxiliary, size);
        --size;
    }
}

static int reverse_9_to_6(int value) {
    if (9 == value / 10) {
        value -= 30;
    }
    if (9 == value % 10) {
        value -= 3;
    }
    return value;
}

static int check_digits(Array_list *ways, int start, int end, Array *squares, Set **arrangements, int size) {
    for (int i = 0; i < SIZE_SET; ++i) {
        arrangements[i] = NULL;
    }
    for (int i = 0; i < size; ++i) {
        int pivot = ways->value[start][i];
        for (int j = 0; j < size; ++j) {
            int value = ways->value[end][j];
            append_set(pivot * 10 + value, arrangements);
            append_set(value * 10 + pivot, arrangements);
        }
    }

    for (int i = 0; i < squares->length; ++i) {
        if (!contains(squares->value[i], arrangements)) {
            return 0;
        }
    }
    return 1;
}

static void append_array(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = value;
    ++array->length;
}

static void append_array_list(int *value, Array_list *array, int size) {
    if (array->length >= array->capacity) {
        array->value = (int **) realloc(array->value, sizeof(int *) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = (int *) malloc(sizeof(int) * size);
    memcpy(array->value[array->length], value, sizeof(int) * size);
    ++array->length;
}

static void append_set(int value, Set **set) {
    int index = value % SIZE_SET;
    if (!set[index]) {
        set[index] = (Set *) malloc(sizeof(Set));
        set[index]->value = value;
        set[index]->next = NULL;
        return;
    }

    Set *current = set[index];
    if (current->value == value) {
        return;
    }

    while (current->next) {
        current = current->next;
        if (current->value == value) {
            return;
        }
    }
    current->next = (Set *) malloc(sizeof(Set));
    current->next->value = value;
    current->next->next = NULL;
}

static int contains(int value, Set **set) {
    Set *current = set[value % SIZE_SET];
    while (current) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
