#include <stdio.h>

#define LENGTH 8

static int get_ways(int target, int *coins, int index);

void Problem031(void) {
    int target = 200;
    int coins[LENGTH] = {1, 2, 5, 10, 20, 50, 100, 200};
    int result = get_ways(target, coins, LENGTH - 1);
    printf("%d\n", result);
}

static int get_ways(int target, int *coins, int index) {
    if (!target || !index) {
        return 1;
    }

    if (target < coins[index]) {
        return get_ways(target, coins, index - 1);
    }
    return get_ways(target, coins, index - 1) + get_ways(target - coins[index], coins, index);
}
