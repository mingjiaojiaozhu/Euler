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
static int check_prime(int value, Array *primes);
static int merge(int head, int tail);
static void search(Array *primes, int **edges, Array *cliques, Array *indexes, int target);
static Array *get_adjacents(int **edges, Array *indexes, int start);
static Array *create_array(void);
static void append(int value, Array *array);
static void clear(int value, Array *array);

void Problem060(void) {
    int target = 5;
    Array *primes = create_array();
    for (int i = 3; i < 10000; i += 2) {
        if (is_prime(i)) {
            append(i, primes);
        }
    }

    int **edges = (int **) malloc(sizeof(int *) * primes->length);
    for (int i = 0; i < primes->length; ++i) {
        edges[i] = (int *) malloc(sizeof(int) * primes->length);
        for (int j = 0; j < primes->length; ++j) {
            edges[i][j] = 0;
        }
    }
    for (int i = 1; i < primes->length; ++i) {
        int value = primes->value[i];
        if (check_prime(merge(3, value), primes) && check_prime(merge(value, 3), primes)) {
            edges[0][i] = 1;
            edges[i][0] = 1;
        }
    }
    for (int i = 1; i < primes->length; ++i) {
        int pivot = primes->value[i];
        for (int j = i + 1; j < primes->length; ++j) {
            int value = primes->value[j];
            if (pivot % 3 == value % 3 && check_prime(merge(pivot, value), primes) && check_prime(merge(value, pivot), primes)) {
                edges[i][j] = 1;
                edges[j][i] = 1;
            }
        }
    }

    Array *cliques = create_array();
    Array *indexes = create_array();
    for (int i = 0; i < primes->length; ++i) {
        append(i, indexes);
    }
    search(primes, edges, cliques, indexes, target);
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

static int check_prime(int value, Array *primes) {
    if (value < 10000) {
        int start = 0;
        int end = primes->length - 1;
        while (start <= end) {
            int current = start + ((end - start) >> 1);
            int prime = primes->value[current];
            if (prime == value) {
                return 1;
            }

            if (prime < value) {
                start = current + 1;
            } else {
                end = current - 1;
            }
        }
        return 0;
    }

    int border = (int) sqrt(value);
    for (int i = 0; i < primes->length; ++i) {
        int prime = primes->value[i];
        if (prime > border) {
            break;
        }
        if (!(value % prime)) {
            return 0;
        }
    }
    return 1;
}

static int merge(int head, int tail) {
    return head * (int) pow(10, (int) log10(tail) + 1) + tail;
}

static void search(Array *primes, int **edges, Array *cliques, Array *indexes, int target) {
    if (!indexes->length) {
        if (cliques->length == target) {
            int result = 0;
            for (int i = 0; i < cliques->length; ++i) {
                result += primes->value[cliques->value[i]];
            }
            printf("%d\n", result);
        }
        return;
    }

    int start = indexes->value[0];
    for (int i = indexes->length - 1; i >= 0; --i) {
        int index = indexes->value[i];
        if (!edges[start][index]) {
            append(index, cliques);
            search(primes, edges, cliques, get_adjacents(edges, indexes, index), target);
            --cliques->length;
            clear(index, indexes);
        }
    }
}

static Array *get_adjacents(int **edges, Array *indexes, int start) {
    Array *auxiliary = create_array();
    for (int i = 0; i < indexes->length; ++i) {
        int index = indexes->value[i];
        if (edges[start][index]) {
            append(index, auxiliary);
        }
    }
    return auxiliary;
}

static Array *create_array(void) {
    Array *array = (Array *) malloc(sizeof(Array));
    array->value = (int *) malloc(sizeof(int) * SIZE);
    array->length = 0;
    array->capacity = SIZE;
    return array;
}

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}

static void clear(int value, Array *array) {
    int index = 0;
    while (index < array->length) {
        if (value == array->value[index]) {
            break;
        }
        ++index;
    }
    for (int i = index + 1; i < array->length; ++i) {
        array->value[i - 1] = array->value[i];
    }
    --array->length;
}
