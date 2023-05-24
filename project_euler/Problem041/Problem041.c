#include <stdio.h>
#include <math.h>

#define LENGTH 7

static int permutation(int *elements, int index, int pivot);
static int is_prime(int value);
static void swap(int *p, int *q);

void Problem041(void) {
    int elements[LENGTH] = {7, 6, 5, 4, 3, 2, 1};
    int result = permutation(elements, 0, 0);
    printf("%d\n", result);
}

static int permutation(int *elements, int index, int pivot) {
    if (index == LENGTH) {
        int result = 0L;
        for (int i = 0; i < LENGTH; ++i) {
            result = result * 10 + elements[i];
        }
        if (is_prime(result)) {
            return (result < pivot) ? pivot : result;
        }
        return pivot;
    }

    int result = permutation(elements, index + 1, pivot);
    for (int i = index + 1; i < LENGTH; ++i) {
        swap(&elements[index], &elements[i]);
        result = permutation(elements, index + 1, result);
        swap(&elements[index], &elements[i]);
    }
    return result;
}

static int is_prime(int value) {
    if (1 != value % 6 && 5 != value % 6) {
        return (2 == value || 3 == value) ? 1 : 0;
    }

    int border = (int) sqrt(value);
    for (int i = 5; i <= border; i += 6) {
        if (!(value % i) || !(value % (i + 2))) {
            return 0;
        }
    }
    return (1 != value) ? 1 : 0;
}

static void swap(int *p, int *q) {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
}
