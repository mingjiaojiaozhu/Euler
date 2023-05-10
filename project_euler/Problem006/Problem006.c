#include <stdio.h>

void Problem006(void) {
    int target = 100;
    int result = target * (target - 1) * (target + 1) * (3 * target + 2) / 12;
    printf("%d\n", result);
}
