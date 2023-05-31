#include <stdio.h>
#include <stdlib.h>

#define LENGTH 8

void Problem031(void) {
    int target = 200;
    int coins[LENGTH] = {1, 2, 5, 10, 20, 50, 100, 200};
    int *ways = (int *) malloc(sizeof(int) * (target + 1));
    for (int i = 1; i <= target; ++i) {
        ways[i] = 0;
    }
    ways[0] = 1;
    for (int i = 0; i < LENGTH; ++i) {
        int coin = coins[i];
        for (int j = coin; j <= target; ++j) {
            ways[j] += ways[j - coin];
        }
    }
    printf("%d\n", ways[target]);
}
