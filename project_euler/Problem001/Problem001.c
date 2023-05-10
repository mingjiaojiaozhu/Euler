#include <stdio.h>

static int get_summation(int border, int factor);

void Problem001(void) {
    int target = 1000;
    int result = get_summation(target, 3) + get_summation(target, 5) - get_summation(target, 3 * 5);
    printf("%d\n", result);
}

static int get_summation(int border, int factor) {
    int count = (border - 1) / factor;
    return factor * count * (count + 1) >> 1;
}
