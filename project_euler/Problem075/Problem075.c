#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 65536

typedef struct node {
    int key;
    int value;
    struct node *next;
} Map;

static int is_relatively_prime(int i, int j);
static void append(int key, Map **map);

void Problem075(void) {
    int target = 1500000;
    int border = (int) sqrt(target >> 1);
    Map **perimeters = (Map **) malloc(sizeof(Map *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        perimeters[i] = NULL;
    }
    for (int i = 2; i <= border; ++i) {
        for (int j = 1; j < i; ++j) {
            if (((i + j) & 1) && is_relatively_prime(i, j)) {
                int pivot = i * (i + j) << 1;
                int length = pivot;
                while (length < target) {
                    append(length, perimeters);
                    length += pivot;
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < SIZE; ++i) {
        Map *current = perimeters[i];
        while (current) {
            if (1 == current->value) {
                ++result;
            }
            current = current->next;
        }
    }
    printf("%d\n", result);
}

static int is_relatively_prime(int i, int j) {
    while (i % j) {
        int auxiliary = i % j;
        i = j;
        j = auxiliary;
    }
    return (1 == j) ? 1 : 0;
}

static void append(int key, Map **map) {
    int index = key % SIZE;
    if (!map[index]) {
        map[index] = (Map *) malloc(sizeof(Map));
        map[index]->key = key;
        map[index]->value = 1;
        map[index]->next = NULL;
        return;
    }

    Map *current = map[index];
    if (current->key == key) {
        ++current->value;
        return;
    }

    while (current->next) {
        current = current->next;
        if (current->key == key) {
            ++current->value;
            return;
        }
    }
    current->next = (Map *) malloc(sizeof(Map));
    current->next->key = key;
    current->next->value = 1;
    current->next->next = NULL;
}
