#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024

static char **split(char *line, const char *delimiter, int length);

void Problem082(void) {
    char *file_name = "matrix.txt";
    int border = 80;
    int **target = (int **) malloc(sizeof(int *) * border);
    for (int i = 0; i < border; ++i) {
        target[i] = (int *) malloc(sizeof(int) * border);
    }

    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    int index = 0;
    while (fgets(line, LENGTH, handle)) {
        line[(int) strlen(line) - 1] = 0x00;
        char **elements = split(line, " ", border);
        for (int i = 0; i < border; ++i) {
            target[index][i] = atoi(elements[i]);
        }
        ++index;
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);

    int *ways = (int *) malloc(sizeof(int) * border);
    for (int i = 0; i < border; ++i) {
        ways[i] = target[i][border - 1];
    }
    for (int i = border - 2; i >= 0; --i) {
        ways[0] += target[0][i];
        for (int j = 1; j < border; ++j) {
            if (ways[j] > ways[j - 1]) {
                ways[j] = ways[j - 1] + target[j][i];
            } else {
                ways[j] += target[j][i];
            }
        }
        for (int j = border - 2; j >= 0; --j) {
            if (ways[j] > ways[j + 1] + target[j][i]) {
                ways[j] = ways[j + 1] + target[j][i];
            }
        }
    }

    int result = ways[0];
    for (int i = 1; i < border; ++i) {
        int value = ways[i];
        if (result > value) {
            result = value;
        }
    }
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
