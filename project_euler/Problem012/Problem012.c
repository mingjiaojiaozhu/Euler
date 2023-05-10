#include <stdio.h>

static int get_divisors(int value);

void Problem012(void) {
    int target = 500;
    int previous = get_divisors(1);
    int index = 1;
    while (1) {
        int current = get_divisors(index + 1);
        int value = previous * current;
        if (value > target) {
            break;
        }

        ++index;
        previous = current;
    }
    int result = index * (index + 1) >> 1;
    printf("%d\n", result);
}

static int get_divisors(int value) {
    int result = 1;
    if (!(value & 1)) {
        int power = 0;
        while (!(value & 1)) {
            value >>= 1;
            ++power;
        }
        result *= power;
    }

    int factor = 3;
    while (factor <= value) {
        int power = 0;
        while (!(value % factor)) {
            value /= factor;
            ++power;
        }
        result *= power + 1;
        factor += 2;
    }
    return result;
}
