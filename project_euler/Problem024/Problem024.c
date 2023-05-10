#include <stdio.h>
#include <string.h>

#define LENGTH 10

static void permutation(long long target, int *pivot, int start);
static long long get_factorial(int value);

void Problem024(void) {
    long long target = 1000000L;
    int elements[LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    permutation(target - 1, elements, 0);

    long long result = 0L;
    for (int i = 0; i < LENGTH; ++i) {
        result = result * 10 + elements[i];
    }
    printf("%lld\n", result);
}

static void permutation(long long sequence, int *elements, int start) {
    if (1 == LENGTH - start) {
        return;
    }

    long long count = get_factorial(LENGTH - start - 1);
    int index = (int) (sequence / count) + start;
    if (index != start) {
        int auxiliary = elements[index];
        memcpy(elements + start + 1, elements + start, sizeof(int) * (index - start));
        elements[start] = auxiliary;
    }
    ++start;
    permutation(sequence % count, elements, start);
}

static long long get_factorial(int value) {
    long long result = 1L;
    for (int i = 2; i <= value; ++i) {
        result *= i;
    }
    return result;
}
