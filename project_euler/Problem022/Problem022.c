#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024
#define SIZE 64

typedef struct {
    char **value;
    int length;
    int capacity;
} Array;

static void append(char *value, Array *array);
static int compare(const void *p, const void *q);

void Problem022(void) {
    char *file_name = "names.txt";
    Array *names = (Array *) malloc(sizeof(Array));
    names->value = (char **) malloc(sizeof(char *) * SIZE);
    names->length = 0;
    names->capacity = SIZE;

    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    while (fgets(line, LENGTH, handle)) {
        append(line, names);
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);

    qsort(names->value, names->length, sizeof(char *), compare);

    long long result = 0L;
    for (int i = names->length - 1; i >= 0; --i) {
        int score = 0;
        for (char *p = names->value[i]; *p; ++p) {
            score += *p - 'A' + 1;
        }
        result += (long long) score * (i + 1);
    }
    printf("%lld\n", result);
}

static void append(char *value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (char **) realloc(array->value, sizeof(char *) * (array->capacity + SIZE));
        array->capacity += SIZE;
    }

    int length = (int) strlen(value);
    array->value[array->length] = (char *) malloc(sizeof(char) * length);
    memset(array->value[array->length], 0x00, sizeof(char) * length);
    memcpy(array->value[array->length], value, sizeof(char) * (length - 1));
    ++array->length;
}

static int compare(const void *p, const void *q) {
    return strcmp(*(char **) p, *(char **) q);
}
