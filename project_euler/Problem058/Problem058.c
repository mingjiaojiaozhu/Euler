#include <stdio.h>
#include <math.h>

static int is_prime(int value);

void Problem058(void) {
    double target = 0.1;
    int index = 3;
    int count = 0;
    while (1) {
        int value = index * index;
        for (int i = 0; i < 3; ++i) {
            value -= index - 1;
            if (is_prime(value)) {
                ++count;
            }
        }

        if ((double) count < ((index << 1) - 1) * target) {
            printf("%d\n", index);
            return;
        }
        index += 2;
    }
}

static int is_prime(int value) {
    if (1 != value % 6 && 5 != value % 6) {
        return (2 == value || 3 == value) ? 1 : 0;
    }

    int border = (int) sqrt(value);
    for (int i = 5; i <= border; i += 6) {
        if (!(value % i) || !(value % (i + 2))) {
            return 0;
        }
    }
    return (1 != value) ? 1 : 0;
}
