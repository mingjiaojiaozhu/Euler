#include <stdio.h>
#include <string.h>

#define LENGTH 1024

void Problem089(void) {
    char *file_name = "roman.txt";
    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    int result = 0;
    while (fgets(line, LENGTH, handle)) {
        line[(int) strlen(line) - 1] = 0x00;
        char previous = ' ';
        char pivot = ' ';
        int count = 1;
        for (char *p = line; *p; ++p) {
            if (pivot == *p) {
                ++count;
            } else {
                previous = pivot;
                pivot = *p;
                count = 1;
            }

            if (count >= 4) {
                if (('I' == pivot && 'V' == previous) || ('X' == pivot && 'L' == previous) || ('C' == pivot && 'D' == previous)) {
                    result += 3;
                } else if ('M' != pivot) {
                    result += 2;
                }
            }
        }
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);
    printf("%d\n", result);
}
