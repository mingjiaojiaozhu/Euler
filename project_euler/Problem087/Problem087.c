#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH 3
#define SIZE_ARRAY 64
#define SIZE_SET 1048576

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

typedef struct node {
    int value;
    struct node *next;
} Set;

static void get_primes(Array **primes, int pivot, int size);
static int is_prime(int value);
static int get_index(int value, Array *primes);
static Array *create_array(void);
static void append_array(int value, Array *array);
static void append_set(int value, Set **set);
static int get_count(Set **set);

void Problem087(void) {
    int target = 50000000;
    Array *primes[3];
    for (int i = 0; i < 3; ++i) {
        primes[i] = create_array();
    }
    get_primes(primes, 2, 3);

    int borders[LENGTH] = {(int) sqrt(target), (int) pow(target, (double) 1 / 3), (int) pow(target, (double) 1 / 4)};
    int index = 3;
    for (int i = 2; i >= 0; --i) {
        int size = i + 1;
        while (index < borders[i]) {
            if (is_prime(index)) {
                get_primes(primes, index, size);
            }
            index += 2;
        }
    }

    Set **summations = (Set **) malloc(sizeof(Set *) * SIZE_SET);
    for (int i = 0; i < SIZE_SET; ++i) {
        summations[i] = NULL;
    }
    for (int i = 0; i < primes[2]->length; ++i) {
        int prime = primes[2]->value[i];
        int pivot = target - prime;
        int border = get_index(pivot, primes[1]);
        for (int j = 0; j < border; ++j) {
            int value = primes[1]->value[j];
            int end = get_index(pivot - value, primes[0]);
            for (int k = 0; k < end; ++k) {
                append_set(prime + value + primes[0]->value[k], summations);
            }
        }
    }
    printf("%d\n", get_count(summations));
}

static void get_primes(Array **primes, int pivot, int size) {
    int value = pivot;
    for (int i = 0; i < size; ++i) {
        value *= pivot;
        append_array(value, primes[i]);
    }
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

static int get_index(int value, Array *primes) {
    int start = 0;
    int end = primes->length - 1;
    while (start <= end) {
        int current = start + ((end - start) >> 1);
        if (primes->value[current] <= value) {
            start = current + 1;
        } else {
            end = current - 1;
        }
    }
    return start;
}

static Array *create_array(void) {
    Array *array = (Array *) malloc(sizeof(Array));
    array->value = (int *) malloc(sizeof(int) * SIZE_ARRAY);
    array->length = 0;
    array->capacity = SIZE_ARRAY;
    return array;
}

static void append_array(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = value;
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

static int get_count(Set **set) {
    int count = 0;
    for (int i = 0; i < SIZE_SET; ++i) {
        Set *current = set[i];
        while (current) {
            ++count;
            current = current->next;
        }
    }
    return count;
}
