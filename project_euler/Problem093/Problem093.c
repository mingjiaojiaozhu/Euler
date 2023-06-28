#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LENGTH 10
#define LENGTH_SIGN 4
#define SIZE_ARRAY 64
#define SIZE_SET 256

typedef struct {
    int border;
    int value;
} Arithmetic;

typedef struct {
    char **value;
    int length;
    int capacity;
} Array;

typedef struct node {
    int value;
    struct node *next;
} Set;

static void get_operations(char *signs, Array *operations);
static void combination(int *elements, int index, int count, int *auxiliary, int size, Array *operations, Arithmetic *pivot, Set **calculations);
static void search(char *signs, int count, Array *operations, char *auxiliary, int size);
static void permutation(int *auxiliary, int start, int length, Array *operations, Set **calculations);
static void add_calculations(double value, Set **calculations);
static double calculate(char sign, double i, double j);
static void swap(int *p, int *q);
static void append_array(char *value, Array *array, int size);
static void append_set(int value, Set **set);
static int contains(int value, Set **set);

void Problem093(void) {
    char signs[LENGTH_SIGN] = {'+', '-', '*', '/'};
    Array *operations = (Array *) malloc(sizeof(Array));
    operations->value = (char **) malloc(sizeof(char *) * SIZE_ARRAY);
    operations->length = 0;
    operations->capacity = SIZE_ARRAY;
    get_operations(signs, operations);

    int elements[LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int auxiliary[4];
    Arithmetic *result = (Arithmetic *) malloc(sizeof(Arithmetic));
    Set **calculations = (Set **) malloc(sizeof(Set *) * SIZE_SET);
    for (int i = 0; i < SIZE_SET; ++i) {
        calculations[i] = NULL;
    }
    combination(elements, 0, 4, auxiliary, 0, operations, result, calculations);
    printf("%d\n", result->value);
}

static void get_operations(char *signs, Array *operations) {
    char auxiliary[3];
    search(signs, 3, operations, auxiliary, 0);
}

static void combination(int *elements, int index, int count, int *auxiliary, int size, Array *operations, Arithmetic *pivot, Set **calculations) {
    if (count == size) {
        for (int i = 0; i < SIZE_SET; ++i) {
            calculations[i] = NULL;
        }
        permutation(auxiliary, 0, count, operations, calculations);
        int border = 1;
        while (contains(border, calculations)) {
            ++border;
        }
        --border;
        if (pivot->border < border) {
            pivot->border = border;
            pivot->value = 0;
            for (int i = 0; i < size; ++i) {
                pivot->value = pivot->value * 10 + auxiliary[i];
            }
        }
        return;
    }

    for (int i = index; i < LENGTH; ++i) {
        auxiliary[size] = elements[i];
        ++size;
        combination(elements, i + 1, count, auxiliary, size, operations, pivot, calculations);
        --size;
    }
}

static void search(char *signs, int count, Array *operations, char *auxiliary, int size) {
    if (count == size) {
        append_array(auxiliary, operations, count);
        return;
    }

    for (int i = 0; i < LENGTH_SIGN; ++i) {
        auxiliary[size] = signs[i];
        ++size;
        search(signs, count, operations, auxiliary, size);
        --size;
    }
}

static void permutation(int *elements, int index, int length, Array *operations, Set **calculations) {
    if (index == length) {
        for (int i = 0; i < operations->length; ++i) {
            add_calculations(calculate(operations->value[i][2], calculate(operations->value[i][1], calculate(operations->value[i][0], elements[0], elements[1]), elements[2]), elements[3]), calculations);
            add_calculations(calculate(operations->value[i][1], calculate(operations->value[i][0], elements[0], elements[1]), calculate(operations->value[i][2], elements[2], elements[3])), calculations);
            add_calculations(calculate(operations->value[i][2], calculate(operations->value[i][0], elements[0], calculate(operations->value[i][1], elements[1], elements[2])), elements[3]), calculations);
            add_calculations(calculate(operations->value[i][0], elements[0], calculate(operations->value[i][2], calculate(operations->value[i][1], elements[1], elements[2]), elements[3])), calculations);
            add_calculations(calculate(operations->value[i][0], elements[0], calculate(operations->value[i][1], elements[1], calculate(operations->value[i][2], elements[2], elements[3]))), calculations);
        }
        return;
    }

    permutation(elements, index + 1, length, operations, calculations);
    for (int i = index + 1; i < length; ++i) {
        swap(&elements[index], &elements[i]);
        permutation(elements, index + 1, length, operations, calculations);
        swap(&elements[index], &elements[i]);
    }
}

static void add_calculations(double value, Set **calculations) {
    if (value > 0 && fabs(floor(value + 0.5) - value) < 0.00000001) {
        append_set((int) value, calculations);
    }
}

static double calculate(char sign, double i, double j) {
    if ('+' == sign) {
        return i + j;
    }
    if ('-' == sign) {
        return i - j;
    }
    if ('*' == sign) {
        return i * j;
    }
    if (fabs(j) < 0.00000001) {
        return -1.0;
    }
    return i / j;
}

static void swap(int *p, int *q) {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
}

static void append_array(char *value, Array *array, int size) {
    if (array->length >= array->capacity) {
        array->value = (char **) realloc(array->value, sizeof(char *) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = (char *) malloc(sizeof(char) * size);
    memcpy(array->value[array->length], value, sizeof(char) * size);
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
