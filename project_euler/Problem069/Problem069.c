#include <stdio.h>
#include <math.h>

static int is_prime(int value);

void Problem069(void) {
    int target = 1000000;
    int index = 3;
    int result = 2;
    while (1) {
        if (is_prime(index)) {
            if (result * index >= target) {
                printf("%d\n", result);
                return;
            }
            result *= index;
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
