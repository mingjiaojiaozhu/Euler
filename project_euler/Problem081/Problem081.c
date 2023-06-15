#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024

static char **split(char *line, const char *delimiter, int length);

void Problem081(void) {
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

    for (int i = 1; i < border; ++i) {
        target[0][i] += target[0][i - 1];
        target[i][0] += target[i - 1][0];
    }
    for (int i = 1; i < border; ++i) {
        for (int j = 1; j < border; ++j) {
            target[i][j] += (target[i - 1][j] < target[i][j - 1]) ? target[i - 1][j] : target[i][j - 1];
        }
    }
    printf("%d\n", target[border - 1][border - 1]);
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
