#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 256

typedef struct node {
    int value;
    struct node *next;
} Set;

static int is_prime(int value);
static void append(int value, Set **set);
static int contains(int value, Set **set);

void Problem046(void) {
    Set **primes = (Set **) malloc(sizeof(Set *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        primes[i] = NULL;
    }
    append(2, primes);
    int result = 3;
    while (1) {
        if (is_prime(result)) {
            append(result, primes);
        } else {
            int border = (int) sqrt((result - 1) >> 1);
            int is_goldbach = 0;
            for (int i = 1; i <= border; ++i) {
                if (contains(result - (i * i << 1), primes)) {
                    is_goldbach = 1;
                    break;
                }
            }
            if (!is_goldbach) {
                printf("%d\n", result);
                return;
            }
        }
        result += 2;
    }
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
