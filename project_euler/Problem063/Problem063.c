#include <stdio.h>
#include <math.h>

void Problem063(void) {
    int result = 0;
    for (int i = 1; i < 10; ++i) {
        result += (int) ((double) 1 / (1 - log10(i)));
    }
    printf("%d\n", result);
}
