#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

typedef struct node {
    int key;
    int value;
    struct node *next;
} Map;

static int get_fractions(int target, Map **fractions);
static int get_count(int value);
static void append(int key, int value, Map **map);
static int get_value(int key, Map **map);

void Problem073(void) {
    int target = 12000;
    Map **fractions = (Map **) malloc(sizeof(Map *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        fractions[i] = NULL;
    }
    append(1, get_count(1), fractions);
    int result = get_fractions(target, fractions) - get_value(1, fractions);
    printf("%d\n", result);
}

static int get_fractions(int target, Map **fractions) {
    int value = get_value(target, fractions);
    if (-1 != value) {
        return value;
    }

    int index = 2;
    int result = 0;
    while (index <= target) {
        int step = target / (target / index);
        result += (step - index + 1) * get_fractions(target / step, fractions);
        index = step + 1;
    }
    result = get_count(target) - result;
    append(target, result, fractions);
    return result;
}

static int get_count(int value) {
    int quotient = value / 6;
    int remainder = value % 6;
    if (5 == remainder) {
        return quotient * (quotient * 3 - 2 + remainder) + 1;
    }
    return quotient * (quotient * 3 - 2 + remainder);
}

static void append(int key, int value, Map **map) {
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

static int get_value(int key, Map **map) {
    Map *current = map[key % SIZE];
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}
