#include <stdio.h>

static void get_digits(int value, int *digits);
static int check_digits(int *digits);

void Problem052(void) {
    int target = 6;
    int digits[2][10];
    int index = 10;
    while (1) {
        get_digits(index, digits[0]);
        int is_same = 1;
        for (int i = target; i > 1; --i) {
            get_digits(index * i, digits[1]);
            if (!check_digits((int *) digits)) {
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

static int check_digits(int *digits) {
    for (int i = 0; i < 10; ++i) {
        if (digits[i] != digits[i + 10]) {
            return 0;
        }
    }
    return 1;
}
