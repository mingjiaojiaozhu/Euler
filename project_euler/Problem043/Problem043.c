#include <stdio.h>

static long long check13(int *elements, int pivot, int *digits);
static long long check17(int *elements, int pivot, int *digits);
static void fill(int *elements, int *digits);
static long long permutation(int *elements, int index, int length);
static void swap(int *p, int *q);

void Problem043(void) {
    int elements[10];
    elements[5] = 5;
    int digits[10];
    for (int i = 0; i < 10; ++i) {
        digits[i] = 0;
    }
    digits[5] = 1;

    int start = 500;
    while (start % 11) {
        ++start;
    }

    long long result = 0L;
    for (int i = start; i < 600; i += 11) {
        elements[6] = (i % 100) / 10;
        elements[7] = i % 10;
        if (5 != elements[6] && 5 != elements[7] && elements[6] != elements[7]) {
            digits[elements[6]] = 1;
            digits[elements[7]] = 1;
            result += check13(elements, elements[6] * 100 + elements[7] * 10, digits);
            digits[elements[6]] = 0;
            digits[elements[7]] = 0;
        }
    }
    printf("%lld\n", result);
}

static long long check13(int *elements, int pivot, int *digits) {
    long long result = 0L;
    for (int i = 0; i < 10; ++i) {
        if (!digits[i] && !((pivot + i) % 13)) {
            elements[8] = i;
            digits[i] = 1;
            result += check17(elements, ((pivot + i) % 100) * 10, digits);
            digits[i] = 0;
        }
    }
    return result;
}

static long long check17(int *elements, int pivot, int *digits) {
    long long result = 0L;
    for (int i = 0; i < 10; ++i) {
        if (!digits[i] && !((pivot + i) % 17)) {
            elements[9] = i;
            digits[i] = 1;
            fill(elements, digits);
            result += permutation(elements, 0, 5);
            digits[i] = 0;
        }
    }
    return result;
}

static void fill(int *elements, int *digits) {
    int index = 4;
    for (int i = 0; i < 10; ++i) {
        if (!digits[i]) {
            elements[index] = i;
            --index;
        }
    }
}

static long long permutation(int *elements, int index, int length) {
    if (index == length) {
        if (!elements[0] || (elements[3] & 1) || (elements[2] + elements[3] + elements[4]) % 3 || (10 * elements[4] + elements[5] - (elements[6] << 1)) % 7) {
            return 0L;
        }

        long long result = 0L;
        for (int i = 0; i < 10; ++i) {
            result = result * 10 + elements[i];
        }
        return result;
    }

    long long result = permutation(elements, index + 1, length);
    for (int i = index + 1; i < length; ++i) {
        swap(&elements[index], &elements[i]);
        result += permutation(elements, index + 1, length);
        swap(&elements[index], &elements[i]);
    }
    return result;
}

static void swap(int *p, int *q) {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
}
