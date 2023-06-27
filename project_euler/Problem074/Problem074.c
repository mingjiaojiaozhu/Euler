#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_ARRAY 64
#define SIZE_SET 256
#define SIZE_MAP 256

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

typedef struct node_set {
    int value;
    struct node_set *next;
} Set;

typedef struct node_map {
    int key;
    int value;
    struct node_map *next;
} Map;

static int get_terms(int value, Set **chains, Map **terms, int *factorials, int *counts);
static int get_permutations(int value, int *factorials, int *counts);
static void get_digits(Array *permutations, Array *auxiliary);
static int get_summation(int value, int *factorials, int *counts);
static Array *create_array(void);
static void append_array(int value, Array *array);
static void append_set(int value, Set **set);
static int contains(int value, Set **set);
static int get_count(Set **set);
static void append_map(int key, int value, Map **map);
static int get_value(int key, Map **map);

void Problem074(void) {
    int target = 60;
    int border = 1000000;
    int step = (int) log10(border);
    Array *permutations = create_array();
    for (int i = 1; i < 10; ++i) {
        append_array(i, permutations);
    }
    Set **chains = (Set **) malloc(sizeof(Set *) * SIZE_SET);
    Map **terms = (Map **) malloc(sizeof(Map *) * SIZE_MAP);
    for (int i = 0; i < SIZE_MAP; ++i) {
        terms[i] = NULL;
    }
    int factorials[10];
    factorials[0] = 1;
    for (int i = 1; i < 10; ++i) {
        factorials[i] = factorials[i - 1] * i;
    }
    int counts[10];
    Array *auxiliary = create_array();
    int result = 0;
    for (int i = 0; i < permutations->length; ++i) {
        int value = permutations->value[i];
        if (target == get_terms(value, chains, terms, factorials, counts)) {
            result += get_permutations(value, factorials, counts);
        }
    }
    for (int i = 1; i < step; ++i) {
        get_digits(permutations, auxiliary);
        for (int j = 0; j < permutations->length; ++j) {
            int value = permutations->value[j];
            if (target == get_terms(value, chains, terms, factorials, counts)) {
                result += get_permutations(value, factorials, counts);
            }
        }
    }
    printf("%d\n", result);
}

static int get_terms(int value, Set **chains, Map **terms, int *factorials, int *counts) {
    for (int i = 0; i < SIZE_SET; ++i) {
        chains[i] = NULL;
    }
    int pivot = value;
    int result;
    while (1) {
        int term = get_value(value, terms);
        if (-1 != term) {
            result = get_count(chains) + term;
            break;
        }
        if (contains(value, chains)) {
            result = get_count(chains);
            break;
        }

        append_set(value, chains);
        value = get_summation(value, factorials, counts);
    }
    append_map(pivot, result, terms);
    return result;
}

static int get_permutations(int value, int *factorials, int *counts) {
    int length = 0;
    int exists_0 = 0;
    for (int i = 0; i < 10; ++i) {
        counts[i] = 0;
    }
    while (value) {
        ++length;
        int remainder = value % 10;
        if (!remainder) {
            exists_0 = 1;
        }
        ++counts[remainder];
        value /= 10;
    }

    int result = factorials[length];
    if (exists_0) {
        result = result * (length - 1) / length;
    }
    for (int i = 0; i < 10; ++i) {
        int count = counts[i];
        if (1 != count) {
            result /= factorials[count];
        }
    }
    return result;
}

static void get_digits(Array *permutations, Array *auxiliary) {
    for (int i = 0; i < permutations->length; ++i) {
        append_array(permutations->value[i], auxiliary);
    }
    permutations->length = 0;
    for (int i = 0; i < auxiliary->length; ++i) {
        int value = auxiliary->value[i];
        int remainder = value % 10;
        for (int j = 0; j <= remainder; ++j) {
            append_array(value * 10 + j, permutations);
        }
    }
    auxiliary->length = 0;
}

static int get_summation(int value, int *factorials, int *counts) {
    int result = 0;
    while (value) {
        result += factorials[value % 10];
        value /= 10;
    }

    for (int i = 0; i < 10; ++i) {
        counts[i] = 0;
    }
    while (result) {
        ++counts[9 - result % 10];
        result /= 10;
    }

    for (int i = 0; i < 10; ++i) {
        int count = counts[i];
        for (int j = 0; j < count; ++j) {
            result = result * 10 + 9 - i;
        }
    }
    return result;
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

static int get_count(Set **set) {
    int result = 0;
    for (int i = 0; i < SIZE_SET; ++i) {
        Set *current = set[i];
        while (current) {
            ++result;
            current = current->next;
        }
    }
    return result;
}

static void append_map(int key, int value, Map **map) {
    int index = key % SIZE_MAP;
    if (!map[index]) {
        map[index] = (Map *) malloc(sizeof(Map));
        map[index]->key = key;
        map[index]->value = value;
        map[index]->next = NULL;
        return;
    }

    Map *current = map[index];
    if (current->key == key) {
        current->value = value;
        return;
    }

    while (current->next) {
        current = current->next;
        if (current->key == key) {
            current->value = value;
            return;
        }
    }
    current->next = (Map *) malloc(sizeof(Map));
    current->next->key = key;
    current->next->value = value;
    current->next->next = NULL;
}

static int get_value(int key, Map **map) {
    Map *current = map[key % SIZE_MAP];
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}
