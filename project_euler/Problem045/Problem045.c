#include <stdio.h>
#include <math.h>

static int is_pentagon(long long value);

void Problem045(void) {
    long long index = 144L;
    while (1) {
        long long hexagon = index * ((index << 1) - 1);
        if (is_pentagon(hexagon)) {
            printf("%lld\n", hexagon);
            return;
        }
        ++index;
    }
}

static int is_pentagon(long long value) {
    double auxiliary = sqrt(value * 24 + 1);
    return (fabs(floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && !(((long long) auxiliary + 1) % 6)) ? 1 : 0;
}
