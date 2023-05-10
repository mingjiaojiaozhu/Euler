#include <stdio.h>

static int get_index(int value, int target);
static int check_combination(int value, int count, int target);

void Problem053(void) {
    int target = 1000000;
    int result = 0;
    for (int i = 23; i <= 100; ++i) {
        result += i + 1 - (get_index(i, target) << 1);
    }
    printf("%d\n", result);
}

static int get_index(int value, int target) {
    int start = 0;
    int end = (value + 1) >> 1;
    while (start <= end) {
        int current = start + ((end - start) >> 1);
        if (check_combination(value, current, target)) {
            start = current + 1;
        } else {
            end = current - 1;
        }
    }
    return start;
}

static int check_combination(int value, int count, int target) {
    int result = 1;
    for (int i = 0; i < count; ++i) {
        result = result * (value - i) / (i + 1);
        if (result > target) {
            return 0;
        }
    }
    return 1;
}
