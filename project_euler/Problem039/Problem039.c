#include <stdio.h>

void Problem039(void) {
    int target = 1000;
    int result = 0;
    int pivot = 0;
    for (int i = target; i >= 2; i -= 2) {
        int count = 0;
        for (int j = i / 3; j > 0; --j) {
            if (!((((i * i) >> 1) - i * j) % (i - j)) && j < (((i * i) >> 1) - i * j) / (i - j)) {
                ++count;
            }
        }
        if (pivot < count) {
            pivot = count;
            result = i;
        }
    }
    printf("%d\n", result);
}
