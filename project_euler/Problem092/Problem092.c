#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 256

typedef struct node {
    int value;
    struct node *next;
} Set;

static int get_chains(int value, Set **chains, int pivot, int *squares);
static int square_digits(int value, int *squares);
static void append(int value, Set **set);
static int contains(int value, Set **set);

void Problem092(void) {
    int target = 10000000;
    int border = 9 * 9 * (int) log10(target);
    Set **chains = (Set **) malloc(sizeof(Set *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        chains[i] = NULL;
    }
    int pivot = 89;
    append(pivot, chains);

    int squares[10];
    for (int i = 0; i < 10; ++i) {
        squares[i] = i * i;
    }

    int result = 0;
    for (int i = 1; i <= border; ++i) {
        if (get_chains(i, chains, pivot, squares)) {
            ++result;
        }
    }
    for (int i = border + 1; i < target; ++i) {
        if (contains(square_digits(i, squares), chains)) {
            ++result;
        }
    }
    printf("%d\n", result);
}

static int get_chains(int value, Set **chains, int pivot, int *squares) {
    if (contains(value, chains) || pivot == value) {
        return 1;
    }
    if (1 == value) {
        return 0;
    }

    int result = get_chains(square_digits(value, squares), chains, pivot, squares);
    if (result) {
        append(value, chains);
    }
    return result;
}

static int square_digits(int value, int *squares) {
    int result = 0;
    while (value) {
        result += squares[value % 10];
        value /= 10;
    }
    return result;
}

static void append(int value, Set **set) {
    int index = value % SIZE;
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
    Set *current = set[value % SIZE];
    while (current) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
