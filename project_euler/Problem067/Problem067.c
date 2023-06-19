#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024

static char **split(char *line, const char *delimiter, int length);
static int maximum(int i, int j);

void Problem067(void) {
    char *file_name = "triangle.txt";
    int border = 100;
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
        char **elements = split(line, " ", index + 1);
        for (int i = 0; i <= index; ++i) {
            target[index][i] = atoi(elements[i]);
        }
        ++index;
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);

    for (int i = border - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            target[i - 1][j] += maximum(target[i][j], target[i][j + 1]);
        }
    }
    printf("%d\n", target[0][0]);
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

static int maximum(int i, int j) {
    return (i > j) ? i : j;
}
