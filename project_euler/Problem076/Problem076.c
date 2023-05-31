#include <stdio.h>
#include <stdlib.h>

void Problem076(void) {
    int target = 100;
    int *ways = (int *) malloc(sizeof(int) * (target + 1));
    for (int i = 1; i <= target; ++i) {
        ways[i] = 0;
    }
    ways[0] = 1;
    for (int i = 1; i < target; ++i) {
        for (int j = i; j <= target; ++j) {
            ways[j] += ways[j - i];
        }
    }
    printf("%d\n", ways[target]);
}
