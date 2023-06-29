#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 256

typedef struct node {
    int value;
    struct node *next;
} Set;

static void get_divisor_summation(int value, long long *divisors, int length);
static int get_chain(long long value, long long *divisors, Set **chains, int target);
static int is_relatively_prime(int i, int j);
static int minimum(int i, int j);
static void append(int value, Set **set);
static int contains(int value, Set **set);

void Problem095(void) {
    int target = 1000000;
    long long *divisors = (long long *) malloc(sizeof(long long) * target);
    for (int i = 0; i < target; ++i) {
        divisors[i] = -1L;
    }
    for (int i = 2; i <= target; ++i) {
        get_divisor_summation(i, divisors, target);
    }
    for (int i = 1; i < target; ++i) {
        divisors[i] -= i + 1;
    }

    int result = 0;
    int pivot = 0;
    Set **chains = (Set **) malloc(sizeof(Set *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        chains[i] = NULL;
    }
    for (int i = 2; i <= target; ++i) {
        int count = get_chain(i, divisors, chains, target);
        if (pivot < count) {
            pivot = count;
            result = target;
            for (int j = 0; j < SIZE; ++j) {
                Set *current = chains[j];
                while (current) {
                    if (result > current->value) {
                        result = current->value;
                    }
                    current = current->next;
                }
            }
        }
    }
    printf("%d\n", result);
}

static void get_divisor_summation(int value, long long *divisors, int length) {
    if (-1 == divisors[value - 1]) {
        long long index = value;
        int count = 1;
        while (index <= length) {
            divisors[(int) index - 1] = ((long long) pow(value, count + 1) - 1) / (value - 1);
            index *= value;
            ++count;
        }

        for (int i = minimum(value - 1, length / value); i >= 2; --i) {
            divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1];
        }
    } else {
        for (int i = minimum(value - 1, length / value); i >= 2; --i) {
            if (is_relatively_prime(value, i) && -1 == divisors[value * i - 1]) {
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1];
            }
        }
    }
}

static int get_chain(long long value, long long *divisors, Set **chains, int target) {
    for (int i = 0; i < SIZE; ++i) {
        chains[i] = NULL;
    }
    append((int) value, chains);

    long long pivot = value;
    int count = 0;
    while (1) {
        value = divisors[(int) value - 1];
        if (pivot == value) {
            break;
        }
        if (1 == value || value >= target || contains((int) value, chains)) {
            return 0;
        }

        append((int) value, chains);
        ++count;
    }
    return count;
}

static int is_relatively_prime(int i, int j) {
    while (i % j) {
        int auxiliary = i % j;
        i = j;
        j = auxiliary;
    }
    return (1 == j) ? 1 : 0;
}

static int minimum(int i, int j) {
    return (i < j) ? i : j;
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
