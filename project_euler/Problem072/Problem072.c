#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

typedef struct node {
    int key;
    long long value;
    struct node *next;
} Map;

static long long get_fractions(int target, Map **fractions);
static long long get_summation(int value);
static void append(int key, long long value, Map **map);
static long long get_value(int key, Map **map);

void Problem072(void) {
    int target = 1000000;
    Map **fractions = (Map **) malloc(sizeof(Map *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        fractions[i] = NULL;
    }
    append(1, get_summation(1), fractions);
    long long result = get_fractions(target, fractions) - get_value(1, fractions);
    printf("%lld\n", result);
}

static long long get_fractions(int target, Map **fractions) {
    long long value = get_value(target, fractions);
    if (-1 != value) {
        return value;
    }

    int index = 2;
    long long result = 0L;
    while (index <= target) {
        int step = target / (target / index);
        result += (step - index + 1) * get_fractions(target / step, fractions);
        index = step + 1;
    }
    result = get_summation(target) - result;
    append(target, result, fractions);
    return result;
}

static long long get_summation(int value) {
    return (long long) value * (value + 1) >> 1;
}

static void append(int key, long long value, Map **map) {
    int index = key % SIZE;
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

static long long get_value(int key, Map **map) {
    Map *current = map[key % SIZE];
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1L;
}
