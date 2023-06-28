#include <stdio.h>

static int common_divisor(int i, int j);
static int minimum(int i, int j);

void Problem091(void) {
    int target = 50;
    int result = target * target * 3;
    for (int i = 1; i < target; ++i) {
        for (int j = 1; j <= target; ++j) {
            int divisor = common_divisor(i, j);
            result += minimum((target - i) * divisor / j, j * divisor / i) << 1;
        }
    }
    printf("%d\n", result);
}

static int common_divisor(int i, int j) {
    while (i % j) {
        int auxiliary = i % j;
        i = j;
        j = auxiliary;
    }
    return j;
}

static int minimum(int i, int j) {
    return (i < j) ? i : j;
}
