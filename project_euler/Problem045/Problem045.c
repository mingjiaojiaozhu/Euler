#include <stdio.h>
#include <math.h>

static int is_pentagon(long long value);

void Problem045(void) {
    long long index = 144;
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
    long long delta = value * 24 + 1;
    return (fabs(floor(sqrt(delta) + 0.5) - sqrt(delta)) < 0.00000001 && !(((long long) sqrt(delta) + 1) % 6)) ? 1 : 0;
}
