#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static void get_palindrome(int value, int *palindromes);
static int is_binary_palindrome(int value, Array *binary);
static void append(int value, Array *array);

void Problem036(void) {
    int target = 1000000;
    int border = (int) ceil(sqrt(target));
    int palindromes[2];

    Array *binary = (Array *) malloc(sizeof(Array));
    binary->value = (int *) malloc(sizeof(int) * SIZE);
    binary->length = 0;
    binary->capacity = SIZE;

    int result = 0;
    for (int i = 1; i < border; ++i) {
        get_palindrome(i, palindromes);
        if (is_binary_palindrome(palindromes[0], binary)) {
            result += palindromes[0];
        }
        if (is_binary_palindrome(palindromes[1], binary)) {
            result += palindromes[1];
        }
    }
    printf("%d\n", result);
}

static void get_palindrome(int value, int *palindromes) {
    palindromes[0] = value / 10;
    palindromes[1] = value;
    while (value) {
        palindromes[0] = palindromes[0] * 10 + value % 10;
        palindromes[1] = palindromes[1] * 10 + value % 10;
        value /= 10;
    }
}

static int is_binary_palindrome(int value, Array *binary) {
    binary->length = 0;
    while (value) {
        binary->value[binary->length] = (value & 1);
        ++binary->length;
        value >>= 1;
    }

    int start = 0;
    int end = binary->length - 1;
    while (start < end) {
        if (binary->value[start] ^ binary->value[end]) {
            return 0;
        }
        ++start;
        --end;
    }
    return 1;
}

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}
