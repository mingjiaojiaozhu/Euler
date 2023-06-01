#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024
#define SIZE 64

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

static void create_elements(int value, int **elements, int *visited);
static void search(int **elements, int start, Array *digits, int *visited, int length);
static void append(int value, Array *array);

void Problem079(void) {
    char *file_name = "keylog.txt";
    int length = 10;
    int **elements = (int **) malloc(sizeof(int *) * length);
    for (int i = 0; i < length; ++i) {
        elements[i] = (int *) malloc(sizeof(int) * length);
        for (int j = 0; j < length; ++j) {
            elements[i][j] = 0;
        }
    }
    int *visited = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        visited[i] = 1;
    }

    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    while (fgets(line, LENGTH, handle)) {
        line[(int) strlen(line) - 1] = 0x00;
        create_elements(atoi(line), elements, visited);
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);

    Array *digits = (Array *) malloc(sizeof(Array));
    digits->value = (int *) malloc(sizeof(int) * SIZE);
    digits->length = 0;
    digits->capacity = SIZE;
    for (int i = 0; i < length; ++i) {
        if (!visited[i]) {
            search(elements, i, digits, visited, length);
        }
    }

    int result = 0;
    for (int i = digits->length - 1; i >= 0; --i) {
        result = result * 10 + digits->value[i];
    }
    printf("%d\n", result);
}

static void create_elements(int value, int **elements, int *visited) {
    int tail = value % 10;
    visited[tail] = 0;
    while (value >= 10) {
        value /= 10;
        int head = value % 10;
        elements[head][tail] = 1;
        tail = head;
        visited[tail] = 0;
    }
}

static void search(int **elements, int start, Array *digits, int *visited, int length) {
    visited[start] = 1;
    int *element = elements[start];
    for (int i = 0; i < length; ++i) {
        if (element[i] && !visited[i]) {
            search(elements, i, digits, visited, length);
        }
    }
    append(start, digits);
}

static void append(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    array->value[array->length] = value;
    ++array->length;
}
