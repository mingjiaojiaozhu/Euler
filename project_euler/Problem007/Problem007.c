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
