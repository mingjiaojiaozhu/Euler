#include <stdio.h>
#include <string.h>

static void get_power(int base, int index, long long *product, long long *auxiliary);
static void get_square(long long *product, long long *auxiliary);
static void get_product(int value, long long *product);

void Problem048(void) {
    int target = 1000;
    long long product[2];
    long long auxiliary[2];
    long long result = 0L;
    for (int i = 1; i <= target; ++i) {
        if (i % 10) {
            get_power(i, i, product, auxiliary);
            result += product[1] * (long long) 1e5 + product[0];
        }
    }
    printf("%lld\n", result % (long long) 1e10);
}

static void get_power(int base, int index, long long *product, long long *auxiliary) {
    if (1 == index) {
        product[0] = base;
        product[1] = 0L;
        return;
    }

    get_power(base, index >> 1, product, auxiliary);
    get_square(product, auxiliary);
    if (index & 1) {
        get_product(base, product);
    }
}

static void get_square(long long *product, long long *auxiliary) {
    auxiliary[0] = product[0] * product[0];
    auxiliary[1] = product[0] * product[1] + product[1] * product[0];
    if (auxiliary[0] >= (long long) 1e5) {
        auxiliary[1] += auxiliary[0] / (long long) 1e5;
        auxiliary[0] %= (long long) 1e5;
    }
    auxiliary[1] %= (long long) 1e5;
    memcpy(product, auxiliary, sizeof(long long) * 2);
}

static void get_product(int value, long long *product) {
    product[0] *= value;
    product[1] *= value;
    if (product[0] >= (long long) 1e5) {
        product[1] += product[0] / (long long) 1e5;
        product[0] %= (long long) 1e5;
    }
    product[1] %= (long long) 1e5;
}
