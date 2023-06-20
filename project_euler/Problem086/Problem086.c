#include <stdio.h>
#include <math.h>

void Problem086(void) {
    int target = 1000000;
    int count = 0;
    int result = 1;
    while (count < target) {
        ++result;
        for (int i = 3; i < result; ++i) {
            double root = sqrt(result * result + i * i);
            if (fabs(floor(root + 0.5) - root) < 0.00000001) {
                count += i >> 1;
            }
        }
        for (int i = (result << 1) - 1; i >= result; --i) {
            double root = sqrt(result * result + i * i);
            if (fabs(floor(root + 0.5) - root) < 0.00000001) {
                count += result - ((i + 1) >> 1) + 1;
            }
        }
    }
    printf("%d\n", result);
}
