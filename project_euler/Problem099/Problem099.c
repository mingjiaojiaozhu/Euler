#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LENGTH 1024

static char **split(char *line, const char *delimiter, int length);

void Problem099(void) {
    char *file_name = "base_exp.txt";
    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    int index = 1;
    double pivot = 0;
    int result = 0;
    while (fgets(line, LENGTH, handle)) {
        line[(int) strlen(line) - 1] = 0x00;
        char **elements = split(line, " ", 2);
        double value = log(atoi(elements[0])) * atoi(elements[1]);
        if (pivot < value) {
            pivot = value;
            result = index;
        }
        ++index;
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);
    printf("%d\n", result);
}

static char **split(char *line, const char *delimiter, int length) {
    char **elements = (char **) malloc(sizeof(char *) * length);
    int index = 0;
    for (char *current = strtok(line, delimiter); current; current = strtok(NULL, delimiter)) {
        elements[index] = current;
        ++index;
    }
    return elements;
}
