#include <stdio.h>
#include <math.h>

#define LENGTH 7

static long long permutation(int *elements, int index, long long pivot);
static int is_prime(long long value);
static void swap(int *p, int *q);

void Problem041(void) {
    int elements[LENGTH] = {7, 6, 5, 4, 3, 2, 1};
    long long result = permutation(elements, 0, 0L);
    printf("%lld\n", result);
}

static long long permutation(int *elements, int index, long long pivot) {
    if (index == LENGTH) {
        long long result = 0L;
        for (int i = 0; i < LENGTH; ++i) {
            result = result * 10 + elements[i];
        }
        if (is_prime(result)) {
            return (result < pivot) ? pivot : result;
        }
        return pivot;
    }

    long long result = permutation(elements, index + 1, pivot);
    for (int i = index + 1; i < LENGTH; ++i) {
        swap(&elements[index], &elements[i]);
        result = permutation(elements, index + 1, result);
        swap(&elements[index], &elements[i]);
    }
    return result;
}

static int is_prime(long long value) {
    if (!(value & 1)) {
        return (2L == value) ? 1 : 0;
    }

    long long border = (long long) sqrt(value);
    for (long long i = 3L; i <= border; i += 2) {
        if (!(value % i)) {
            return 0;
        }
    }
    return (1L != value) ? 1 : 0;
}

static void swap(int *p, int *q) {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
}
