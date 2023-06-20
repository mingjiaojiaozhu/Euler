#include <stdio.h>
#include <math.h>

static int get_period(int value);

void Problem064(void) {
    int target = 10000;
    int result = 0;
    for (int i = 1; i <= target; ++i) {
        if (get_period(i) & 1) {
            ++result;
        }
    }
    printf("%d\n", result);
}

static int get_period(int value) {
    double auxiliary = sqrt(value);
    if (fabs(floor(auxiliary + 0.5) - auxiliary) < 0.00000001) {
        return 0;
    }

    int initial = (int) auxiliary;
    int pivot = initial << 1;
    int current = initial;
    int offset = 0;
    int factor = 1;
    int count = 0;
    while (current != pivot) {
        offset = current * factor - offset;
        factor = (value - offset * offset) / factor;
        current = (initial + offset) / factor;
        ++count;
    }
    return count;
}
