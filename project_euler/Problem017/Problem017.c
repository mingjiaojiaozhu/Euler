#include <stdio.h>

#define LENGTH 10

void Problem017(void) {
    int letters_below_10[LENGTH - 1] = {3, 3, 5, 4, 4, 3, 5, 5, 4};
    int letters_10_to_19[LENGTH] = {3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
    int letters_whole_ten[LENGTH - 2] = {6, 6, 5, 5, 5, 7, 6, 6};
    int letter_100 = 7;
    int letter_and = 3;
    int letter_1000 = 8;

    int count_below_10 = 0;
    for (int i = LENGTH - 2; i >= 0; --i) {
        count_below_10 += letters_below_10[i];
    }

    int count_below_100 = count_below_10 * 9;
    for (int i = LENGTH - 1; i >= 0; --i) {
        count_below_100 += letters_10_to_19[i];
    }
    for (int i = LENGTH - 3; i >= 0; --i) {
        count_below_100 += letters_whole_ten[i] * 10;
    }

    int result = count_below_100 * 10 + count_below_10 * 100 + letter_100 * 100 * 9 + letter_and * 99 * 9 + letters_below_10[0] + letter_1000;
    printf("%d\n", result);
}
