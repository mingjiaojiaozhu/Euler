#include <stdio.h>
#include <string.h>
#include <math.h>

#define LENGTH 1024

void Problem042(void) {
    char *file_name = "words.txt";
    int result = 0;
    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    while (fgets(line, LENGTH, handle)) {
        int value = 0;
        for (char *p = line; '\n' != *p; ++p) {
            value += *p - 'A' + 1;
        }
        int delta = (value << 3) + 1;
        if (fabs(floor(sqrt(delta) + 0.5) - sqrt(delta)) < 0.00000001 && ((int) sqrt(delta) & 1)) {
            ++result;
        }
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);
    printf("%d\n", result);
}
