#include <stdio.h>
#include <math.h>

static int is_prime(int value);

void Problem027(void) {
    int target = 1000;
    int border = -1 * (target - 1);
    int result = 0;
    int pivot = 0;
    for (int i = 3; i < target; i += 2) {
        if (!is_prime(i)) {
            continue;
        }

        for (int j = border; j < target; j += 2) {
            int count = 1;
            while (is_prime(count * count + count * j + i)) {
                ++count;
            }
            if (pivot < count) {
                pivot = count;
                result = i * j;
            }
        }
    }
    printf("%d\n", result);
}

static int is_prime(int value) {
    if (value <= 0) {
        return 0;
    }
    if (!(value & 1)) {
        return (2 == value) ? 1 : 0;
    }

    int border = (int) sqrt(value);
    for (int i = 3; i <= border; i += 2) {
        if (!(value % i)) {
            return 0;
        }
    }
    return (1 != value) ? 1 : 0;
}
