#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 256

typedef struct node {
    int value;
    struct node *next;
} Set;

static int carry(int *digits, int length);
static void append(int value, Set **set);
static int contains(int value, Set **set);

void Problem088(void) {
    int target = 12000;
    int length = (int) ceil(log(target) / log(2));
    int *products = (int *) malloc(sizeof(int) * (target - 1));
    int initial = (int) pow(2, length + 1);
    for (int i = target - 2; i >= 0; --i) {
        products[i] = initial;
    }

    int *digits = (int *) malloc(sizeof(int) * (length));
    for (int i = 2; i <length; ++i) {
        digits[i] = 1;
    }
    digits[0] = 2;
    digits[1] = 2;

    int pivot = target - length;
    while (1) {
        int product = 1;
        int summation = 0;
        for (int i = 0; i < length; ++i) {
            int value = digits[i];
            product *= value;
            summation += value;
        }
        int difference = product - summation;
        if (difference <= pivot) {
            int index = difference + length - 2;
            if (index >= 0 && products[index] > product) {
                products[index] = product;
            }
            ++digits[0];
        } else {
            if (!carry(digits, length)) {
                break;
            }
        }
    }

    int result = 0;
    Set **auxiliary = (Set **) malloc(sizeof(Set *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        auxiliary[i] = NULL;
    }
    for (int i = target - 2; i >= 0; --i) {
        int value = products[i];
        if (!contains(value, auxiliary)) {
            result += value;
            append(value, auxiliary);
        }
    }
    printf("%d\n", result);
}

static int carry(int *digits, int length) {
    for (int i = 1; i < length; ++i) {
        if (digits[i] != digits[i - 1]) {
            ++digits[i];
            int value = digits[i];
            for (int j = 0; j < i; ++j) {
                digits[j] = value;
            }
            return 1;
        }
    }
    return 0;
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
