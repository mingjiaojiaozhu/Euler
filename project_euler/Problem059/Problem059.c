#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024
#define SIZE_ARRAY 64
#define SIZE_MAP 256

typedef struct {
    int *value;
    int length;
    int capacity;
} Array;

typedef struct node {
    int key;
    int value;
    struct node *next;
} Map;

static void append_array(int value, Array *array);
static void append_map(int key, Map **map);

void Problem059(void) {
    char *file_name = "cipher.txt";
    Array *codes = (Array *) malloc(sizeof(Array));
    codes->value = (int *) malloc(sizeof(int) * SIZE_ARRAY);
    codes->length = 0;
    codes->capacity = SIZE_ARRAY;
    Map **counts[3];
    for (int i = 0; i < 3; ++i) {
        counts[i] = (Map **) malloc(sizeof(Map *) * SIZE_MAP);
        for (int j = 0; j < SIZE_MAP; ++j) {
            counts[i][j] = NULL;
        }
    }

    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    int index = 0;
    while (fgets(line, LENGTH, handle)) {
        line[(int) strlen(line) - 1] = 0x00;
        int code = atoi(line);
        append_array(code, codes);
        append_map(code, counts[index]);
        ++index;
        if (3 == index) {
            index = 0;
        }
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);

    int keys[3];
    for (int i = 0; i < 3; ++i) {
        int pivot = 0;
        for (int j = 0; j < SIZE_MAP; ++j) {
            Map *current = counts[i][j];
            while (current) {
                if (pivot < current->value) {
                    pivot = current->value;
                    keys[i] = current->key;
                }
                current = current->next;
            }
        }
        keys[i] ^= ' ';
    }

    int result = 0;
    index = 0;
    for (int i = 0; i < codes->length; ++i) {
        result += codes->value[i] ^ keys[index];
        ++index;
        if (3 == index) {
            index = 0;
        }
    }
    printf("%d\n", result);
}

static void append_array(int value, Array *array) {
    if (array->length >= array->capacity) {
        array->value = (int *) realloc(array->value, sizeof(int) * (array->capacity + SIZE_ARRAY));
        array->capacity += SIZE_ARRAY;
    }

    array->value[array->length] = value;
    ++array->length;
}

static void append_map(int key, Map **map) {
    int index = key % SIZE_MAP;
    if (!map[index]) {
        map[index] = (Map *) malloc(sizeof(Map));
        map[index]->key = key;
        map[index]->value = 1;
        map[index]->next = NULL;
        return;
    }

    Map *current = map[index];
    if (current->key == key) {
        ++current->value;
        return;
    }

    while (current->next) {
        current = current->next;
        if (current->key == key) {
            ++current->value;
            return;
        }
    }
    current->next = (Map *) malloc(sizeof(Map));
    current->next->key = key;
    current->next->value = 1;
    current->next->next = NULL;
}
