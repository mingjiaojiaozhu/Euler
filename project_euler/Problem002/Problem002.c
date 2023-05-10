#include <stdio.h>

void Problem002(void) {
    int target = 4000000;
    int previous[2] = {2, 8};
    int result = previous[0] + previous[1];
    while (1) {
        int current = previous[0] + (previous[1] << 2);
        if (current > target) {
            break;
        }

        result += current;
        previous[0] = previous[1];
        previous[1] = current;
    }
    printf("%d\n", result);
}
