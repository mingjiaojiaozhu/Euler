#include <stdio.h>
#include <math.h>

static int get_count(int length, int width);
static int minimum(int i, int j);

void Problem085(void) {
    int target = 2000000;
    int border = ((int) sqrt(1 + 8 * sqrt(target)) - 1) >> 1;
    int result = 0;
    int pivot = target;
    for (int i = 1; i <= border; ++i) {
        int length = ((int) sqrt(1 + (double) (target << 4) / i / (i + 1)) - 1) >> 1;
        int value = minimum(abs(get_count(length, i) - target), abs(get_count(length + 1, i) - target));
        if (pivot > value) {
            result = length * i;
            pivot = value;
        }
    }
    printf("%d\n", result);
}

static int get_count(int length, int width) {
    return length * (length + 1) * width * (width + 1) >> 2;
}

static int minimum(int i, int j) {
    return (i < j) ? i : j;
}
