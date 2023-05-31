#include <stdio.h>

void Problem071(void) {
    int target = 1000000;
    int index = (target - 5) / 7;
    int result = index * 3 + 2;
    printf("%d\n", result);
}
