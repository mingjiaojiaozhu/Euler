#include <stdio.h>

#define LENGTH 12

void Problem019(void) {
    int start = 1900;
    int end = 2000;
    int days[LENGTH] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int week = 1;
    for (int i = 0; i < LENGTH; ++i) {
        week += days[i];
    }
    if (!(start % 4) && (start % 100 || !(start % 400))) {
        ++week;
    }
    week %= 7;

    int result = 0;
    for (int i = start + 1; i <= end; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            if (!week) {
                ++result;
            }

            week += days[j];
            if (1 == j && (!(start % 4) && (start % 100 || !(start % 400)))) {
                ++week;
            }
            week %= 7;
        }
    }
    printf("%d\n", result);
}
