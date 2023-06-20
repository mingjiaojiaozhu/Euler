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
        double auxiliary = sqrt((value << 3) + 1);
        if (fabs(floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && ((int) auxiliary & 1)) {
            ++result;
        }
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);
    printf("%d\n", result);
}
