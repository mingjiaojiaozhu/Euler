#include <stdio.h>
#include <math.h>

static int is_prime(int value);

void Problem007(void) {
    int target = 10001;
    int result = 1;
    int count = 1;
    while (count < target) {
        result += 2;
        if (is_prime(result)) {
            ++count;
        }
    }
    printf("%d\n", result);
}

static int is_prime(int value) {
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
