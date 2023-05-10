#include <stdio.h>
#include <math.h>

void Problem025(void) {
    int target = 1000;
    int result = (int) ceil(((double) target - 1 + log10(5) / 2) / log10((1 + sqrt(5)) / 2));
    printf("%d\n", result);
}
