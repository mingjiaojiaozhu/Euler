#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024

typedef struct {
    int index;
    int weight;
} Heap;

typedef struct {
    Heap *values;
    int length;
} Array;

static void search(int **edges, int length, int *result);
static char **split(char *line, const char *delimiter, int length);
static void enqueue(int index, int weight, Array *queue);
static Heap dequeue(Array *queue);

void Problem083(void) {
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

    int length = border * border;
    int **edges = (int **) malloc(sizeof(int *) * length);
    for (int i = 0; i < length; ++i) {
        edges[i] = (int *) malloc(sizeof(int) * length);
        for (int j = 0; j < length; ++j) {
            edges[i][j] = 0;
        }
    }
    for (int i = 0; i < border; ++i) {
        for (int j = 0; j < border; ++j) {
            if (i > 0) {
                edges[i * border + j][(i - 1) * border + j] = target[i - 1][j];
            }
            if (j > 0) {
                edges[i * border + j][i * border + j - 1] = target[i][j - 1];
            }
            if (i < border - 1) {
                edges[i * border + j][(i + 1) * border + j] = target[i + 1][j];
            }
            if (j < border - 1) {
                edges[i * border + j][i * border + j + 1] = target[i][j + 1];
            }
        }
    }

    int *ways = (int *) malloc(sizeof(int) * length);
    search(edges, length, ways);
    printf("%d\n", ways[length - 1] + target[0][0]);
}

static void search(int **edges, int length, int *ways) {
    int *visited = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        visited[i] = 0;
    }
    Array *queue = (Array *) malloc(sizeof(Array));
    queue->values = (Heap *) malloc(sizeof(Heap) * length);
    queue->length = 0;
    enqueue(0, 0, queue);
    while (queue->length > 0) {
        Heap node = dequeue(queue);
        int index = node.index;
        int weight = node.weight;
        if (visited[index]) {
            continue;
        }

        ways[index] = weight;
        visited[index] = 1;
        for (int i = 0; i < length; ++i) {
            if (edges[index][i] && !visited[i]) {
                enqueue(i, weight + edges[index][i], queue);
            }
        }
    }
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

static void enqueue(int index, int weight, Array *queue) {
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent].weight <= weight) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child].index = index;
    queue->values[child].weight = weight;
    ++queue->length;
}

static Heap dequeue(Array *queue) {
    --queue->length;
    Heap value = queue->values[0];
    Heap pivot = queue->values[queue->length];
    int parent = 0;
    while (1) {
        int child = (parent << 1) + 1;
        if (child >= queue->length) {
            break;
        }

        if (child < queue->length - 1 && queue->values[child].weight > queue->values[child + 1].weight) {
            ++child;
        }
        if (queue->values[child].weight >= pivot.weight) {
            break;
        }
        queue->values[parent] = queue->values[child];
        parent = child;
    }
    queue->values[parent] = pivot;
    return value;
}
