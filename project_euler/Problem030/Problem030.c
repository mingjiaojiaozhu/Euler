#include <stdio.h>
#include <math.h>

static int get_power_digit(int value, int *powers);

void Problem030(void) {
    int target = 5;
    int powers[10];
    for (int i = 0; i < 10; ++i) {
        powers[i] = (int) pow(i, target);
    }

    int result = 0;
    for (int i = 6 * powers[9]; i >= 10; --i) {
        if (i == get_power_digit(i, powers)) {
            result += i;
        }
    }
    printf("%d\n", result);
}

static int get_power_digit(int value, int *powers) {
    int result = 0;
    while (value) {
        result += powers[value % 10];
        value /= 10;
    }
    return result;
}
