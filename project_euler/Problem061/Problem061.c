#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int head;
    int tail;
    int step;
} Polygonal;

typedef struct {
    Polygonal **value;
    int length;
    int capacity;
} Array_polygonal;

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static void add_triangle(Array_polygonal *polygonals);
static void add_square(Array_polygonal *polygonals);
static void add_pentagonal(Array_polygonal *polygonals);
static void add_hexagonal(Array_polygonal *polygonals);
static void add_heptagonal(Array_polygonal *polygonals);
static void add_octagonal(Array_polygonal *polygonals);
static void search(Array_polygonal *polygonals, int **edges, int start, Array *indexes, int *steps, int target);
static void append_polygonal(int value, int step, Array_polygonal *array);
static void append(int value, Array *array);

void Problem061(void) {
    int target = 6;
    Array_polygonal *polygonals = (Array_polygonal *) malloc(sizeof(Array_polygonal));
    polygonals->value = (Polygonal **) malloc(sizeof(Polygonal *) * SIZE);
    polygonals->length = 0;
    polygonals->capacity = SIZE;
    add_triangle(polygonals);
    add_square(polygonals);
    add_pentagonal(polygonals);
    add_hexagonal(polygonals);
    add_heptagonal(polygonals);
    add_octagonal(polygonals);

    int **edges = (int **) malloc(sizeof(int *) * polygonals->length);
    for (int i = 0; i < polygonals->length; ++i) {
        edges[i] = (int *) malloc(sizeof(int) * polygonals->length);
        for (int j = 0; j < polygonals->length; ++j) {
            edges[i][j] = 0;
        }
    }
    for (int i = 0; i < polygonals->length; ++i) {
        Polygonal *pivot = polygonals->value[i];
        for (int j = i + 1; j < polygonals->length; ++j) {
            Polygonal *polygonal = polygonals->value[j];
            if (pivot->step != polygonal->step) {
                if (pivot->tail == polygonal->head) {
                    edges[i][j] = 1;
                }
                if (polygonal->tail == pivot->head) {
                    edges[j][i] = 1;
                }
            }
        }
    }

    Array *indexes = (Array *) malloc(sizeof(Array));
    indexes->value = (int *) malloc(sizeof(int) * SIZE);
    indexes->length = 0;
    indexes->capacity = SIZE;
    int *steps = (int *) malloc(sizeof(int) * target);
    for (int i = 0; i < target; ++i) {
        steps[i] = 0;
    }
    int pivot = polygonals->value[0]->step;
    steps[pivot] = 1;
    for (int i = 0; i < polygonals->length; ++i) {
        append(i, indexes);
        int step = polygonals->value[i]->step;
        if (step != pivot) {
            return;
        }
        search(polygonals, edges, i, indexes, steps, target);
        --indexes->length;
    }
}

static void add_triangle(Array_polygonal *polygonals) {
    int index = (int) ceil((sqrt(8001) - 1) / 2);
    while (1) {
        int value = index * (index + 1) >> 1;
        if (value >= 10000) {
            return;
        }
        if (value % 100 >= 10) {
            append_polygonal(value, 0, polygonals);
        }
        ++index;
    }
}

static void add_square(Array_polygonal *polygonals) {
    int index = (int) ceil(sqrt(1000));
    while (1) {
        int value = index * index;
        if (value >= 10000) {
            return;
        }
        if (value % 100 >= 10) {
            append_polygonal(value, 1, polygonals);
        }
        ++index;
    }
}

static void add_pentagonal(Array_polygonal *polygonals) {
    int index = (int) ceil((sqrt(24001) + 1) / 6);
    while (1) {
        int value = index * (3 * index - 1) >> 1;
        if (value >= 10000) {
            return;
        }
        if (value % 100 >= 10) {
            append_polygonal(value, 2, polygonals);
        }
        ++index;
    }
}

static void add_hexagonal(Array_polygonal *polygonals) {
    int index = (int) ceil((sqrt(8001) + 1) / 4);
    while (1) {
        int value = index * ((index << 1) - 1);
        if (value >= 10000) {
            return;
        }
        if (value % 100 >= 10) {
            append_polygonal(value, 3, polygonals);
        }
        ++index;
    }
}

static void add_heptagonal(Array_polygonal *polygonals) {
    int index = (int) ceil((sqrt(40009) + 3) / 10);
    while (1) {
        int value = index * (5 * index - 3) >> 1;
        if (value >= 10000) {
            return;
        }
        if (value % 100 >= 10) {
            append_polygonal(value, 4, polygonals);
        }
        ++index;
    }
}

static void add_octagonal(Array_polygonal *polygonals) {
    int index = (int) ceil((sqrt(12002) + 2) / 6);
    while (1) {
        int value = index * (3 * index - 2);
        if (value >= 10000) {
            return;
        }
        if (value % 100 >= 10) {
            append_polygonal(value, 5, polygonals);
        }
        ++index;
    }
}

static void search(Array_polygonal *polygonals, int **edges, int start, Array *indexes, int *steps, int target) {
    if (indexes->length == target) {
        if (polygonals->value[indexes->value[0]]->head == polygonals->value[indexes->value[target - 1]]->tail) {
            int result = 0;
            for (int i = 0; i < target; ++i) {
                Polygonal *polygonal = polygonals->value[indexes->value[i]];
                result += polygonal->head * 100 + polygonal->tail;
            }
            printf("%d\n", result);
        }
        return;
    }

    for (int i = polygonals->length - 1; i >= 0; --i) {
        if (edges[start][i]) {
            int step = polygonals->value[i]->step;
            if (!steps[step]) {
                append(i, indexes);
                steps[step] = 1;
                search(polygonals, edges, i, indexes, steps, target);
                --indexes->length;
                steps[step] = 0;
            }
        }
    }
}

static void append_polygonal(int value, int step, Array_polygonal *array) {
    if (array->length >= array->capacity) {
        array->value = (Polygonal **) realloc(array->value, sizeof(Polygonal *) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = (Polygonal *) malloc(sizeof(Polygonal));
    array->value[array->length]->head = value / 100;
    array->value[array->length]->tail = value % 100;
    array->value[array->length]->step = step;
    ++array->length;
}

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}
