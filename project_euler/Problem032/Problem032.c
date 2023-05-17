#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

typedef struct node {
    int value;
    struct node *next;
} Set;

static void get_products(int multiplicand, int multiplier, int *digits, Set **products);
static int is_pandigital(int value, int *digits);
static void append(int value, Set **set);

void Problem032(void) {
    int digits[9];
    Set **products = (Set **) malloc(sizeof(Set *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        products[i] = NULL;
    }

    for (int i = 1; i < 10; ++i) {
        for (int j = 10000 / i; j >= 1234; --j) {
            get_products(i, j, digits, products);
        }
    }

    for (int i = 10; i < 100; ++i) {
        for (int j = 10000 / i; j >= 123; --j) {
            get_products(i, j, digits, products);
        }
    }

    int result = 0;
    for (int i = 0; i < SIZE; ++i) {
        Set *current = products[i];
        while (current) {
            result += current->value;
            current = current->next;
        }
    }
    printf("%d\n", result);
}

static void get_products(int multiplicand, int multiplier, int *digits, Set **products) {
    for (int i = 0; i < 9; ++i) {
        digits[i] = 0;
    }

    if (is_pandigital(multiplicand, digits) && is_pandigital(multiplier, digits)) {
        int product = multiplicand * multiplier;
        if (is_pandigital(product, digits)) {
            append(product, products);
        }
    }
}

static int is_pandigital(int value, int *digits) {
    while (value) {
        int index = value % 10 - 1;
        if (index < 0 || digits[index]) {
            return 0;
        }
        digits[index] = 1;
        value /= 10;
    }
    return 1;
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
