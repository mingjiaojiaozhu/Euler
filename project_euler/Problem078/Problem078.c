#include <stdio.h>
#include <stdlib.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
} Decimal;

typedef struct {
    Decimal **value;
    int length;
    int capacity;
} Array;

static Decimal *set_value(int value, int length);
static Decimal *get_way(int target, Array *ways, Decimal *auxiliary);
static int is_divide_exactly(Decimal *way, int length, int target);
static int add_decimal(int index, Array *ways, int factor, Decimal *result);
static void swap_decimal(Decimal *previous, Decimal *current);
static void get_summation(Decimal *decimal, int factor, Decimal *summation);
static void append(Decimal *value, Array *array);
static Decimal *create_array(int length);

void Problem078(void) {
    int target = 1000000;
    Array *ways = (Array *) malloc(sizeof(Array));
    ways->value = (Decimal **) malloc(sizeof(Decimal *) * SIZE);
    ways->length = 0;
    ways->capacity = SIZE;
    append(set_value(1, 1), ways);
    append(set_value(1, 1), ways);

    int length = 0;
    while (target >= (int) 1e5) {
        ++length;
        target /= (int) 1e5;
    }

    Decimal *auxiliary = create_array(100);
    int result = 2;
    while (1) {
        Decimal *way = get_way(result, ways, auxiliary);
        if (is_divide_exactly(way, length, target)) {
            printf("%d\n", result);
            return;
        }
        ++result;
    }
}

static Decimal *set_value(int value, int length) {
    Decimal *decimal = create_array(length);
    decimal->value[0] = value;
    decimal->length = 1;
    return decimal;
}

static Decimal *get_way(int target, Array *ways, Decimal *auxiliary) {
    int factor = 1;
    for (int i = 1; i <= target; ++i) {
        if (!add_decimal(target - (i * (i * 3 - 1) >> 1), ways, factor, auxiliary) || !add_decimal(target - (i * (i * 3 + 1) >> 1), ways, factor, auxiliary)) {
            break;
        }
        factor *= -1;
    }
    Decimal *result = create_array(auxiliary->length);
    swap_decimal(auxiliary, result);
    append(result, ways);
    return result;
}

static int is_divide_exactly(Decimal *way, int length, int target) {
    if (way->length <= length) {
        return 0;
    }

    for (int i = 0; i < length; ++i) {
        if (way->value[i]) {
            return 0;
        }
    }
    return !(way->value[length] % target) ? 1 : 0;
}

static int add_decimal(int index, Array *ways, int factor, Decimal *summation) {
    if (index < 0) {
        return 0;
    }
    get_summation(ways->value[index], factor, summation);
    return 1;
}

static void swap_decimal(Decimal *previous, Decimal *current) {
    int length = (previous->length < current->length) ? current->length : previous->length;
    for (int i = 0; i < length; ++i) {
        previous->value[i] ^= current->value[i];
        current->value[i] ^= previous->value[i];
        previous->value[i] ^= current->value[i];
    }
    previous->length ^= current->length;
    current->length ^= previous->length;
    previous->length ^= current->length;
}

static void get_summation(Decimal *decimal, int factor, Decimal *summation) {
    for (int i = 0; i < decimal->length; ++i) {
        summation->value[i] += decimal->value[i] * factor;
    }

    if (factor > 0) {
        for (int i = 0; i < summation->length; ++i) {
            if (summation->value[i] >= (int) 1e5) {
                summation->value[i + 1] += summation->value[i] / (int) 1e5;
                summation->value[i] %= (int) 1e5;
            }
        }
        if (summation->value[summation->length]) {
            ++summation->length;
        }
    } else {
        for (int i = 0; i < summation->length; ++i) {
            if (summation->value[i] < 0) {
                --summation->value[i + 1];
                summation->value[i] += (int) 1e5;
            }
        }
        while (!summation->value[summation->length - 1]) {
            --summation->length;
        }
    }

}

static void append(Decimal *value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (Decimal **) realloc(array->value, sizeof(Decimal *) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}

static Decimal *create_array(int length) {
    Decimal *decimal = (Decimal *) malloc(sizeof(Decimal));
    decimal->value = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        decimal->value[i] = 0;
    }
    decimal->length = 0;
    return decimal;
}
