#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 256

typedef struct node {
    int value;
    struct node *next;
} Set;

static int is_abundant(int value);
static void append(int value, Set **set);
static int contains(int value, Set **set);

void Problem023(void) {
    int start = 24;
    int end = 28123;
    Set **abundants = (Set **) malloc(sizeof(Set *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        abundants[i] = NULL;
    }
    for (int i = start >> 1; i <= start; ++i) {
        if (is_abundant(i)) {
            append(i, abundants);
        }
    }

    int result = start * (start - 1) >> 1;
    for (int i = start + 1; i <= end; ++i) {
        int is_non_abundant = 1;
        for (int j = 0; j < SIZE; ++j) {
            Set *current = abundants[j];
            while (current) {
                if (contains(i - current->value, abundants)) {
                    is_non_abundant = 0;
                    break;
                }
                current = current->next;
            }
            if (!is_non_abundant) {
                break;
            }
        }
        if (is_non_abundant) {
            result += i;
        }

        if (is_abundant(i)) {
            append(i, abundants);
        }
    }
    printf("%d\n", result);
}

static int is_abundant(int value) {
    int border = (int) sqrt(value);
    int summation = 1;
    for (int i = 2; i < border; ++i) {
        if (!(value % i)) {
            summation += i + value / i;
        }
    }
    if (!(value % border)) {
        summation += border;
        if (value != border * border) {
            summation += value / border;
        }
    }
    return (summation > value) ? 1 : 0;
}

static void append(int value, Set **set) {
    if (!set[value % SIZE]) {
        set[value % SIZE] = (Set *) malloc(sizeof(Set));
        set[value % SIZE]->value = value;
        set[value % SIZE]->next = NULL;
        return;
    }

    Set *current = set[value % SIZE];
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
