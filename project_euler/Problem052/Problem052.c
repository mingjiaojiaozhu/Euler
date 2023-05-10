#include <stdio.h>

static void get_digits(int value, int *digits);
static int check_digits(int *pivots, int *digits);

void Problem052(void) {
    int target = 6;
    int pivots[10];
    int digits[10];
    int index = 10;
    while (1) {
        get_digits(index, pivots);
        int is_same = 1;
        for (int i = target; i > 1; --i) {
            get_digits(index * i, digits);
            if (!check_digits(pivots, digits)) {
                is_same = 0;
                break;
            }
        }
        if (is_same) {
            printf("%d\n", index);
            return;
        }
        ++index;
    }
}

static void get_digits(int value, int *digits) {
    for (int i = 0; i < 10; ++i) {
        digits[i] = 0;
    }

    while (value) {
        ++digits[value % 10];
        value /= 10;
    }
}

static int check_digits(int *pivots, int *digits) {
    for (int i = 0; i < 10; ++i) {
        if (pivots[i] != digits[i]) {
            return 0;
        }
    }
    return 1;
}
