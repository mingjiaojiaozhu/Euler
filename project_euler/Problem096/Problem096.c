#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LENGTH 1024

static int solve(int **sudoku, int index, int border, int factor, int **rows, int **columns, int **boxes);

void Problem096(void) {
    char *file_name = "sudoku.txt";
    int border = 9;
    int factor = (int) sqrt(border);
    int **sudoku = (int **) malloc(sizeof(int *) * border);
    int **rows = (int **) malloc(sizeof(int *) * border);
    int **columns = (int **) malloc(sizeof(int *) * border);
    int **boxes = (int **) malloc(sizeof(int *) * border);
    for (int i = 0; i < border; ++i) {
        sudoku[i] = (int *) malloc(sizeof(int) * border);
        rows[i] = (int *) malloc(sizeof(int) * border);
        columns[i] = (int *) malloc(sizeof(int) * border);
        boxes[i] = (int *) malloc(sizeof(int) * border);
        for (int j = 0; j < border; ++j) {
            rows[i][j] = 0;
            columns[i][j] = 0;
            boxes[i][j] = 0;
        }
    }

    FILE *handle = fopen(file_name, "r");
    char line[LENGTH];
    memset(line, 0x00, sizeof(char) * LENGTH);
    int index = 0;
    int result = 0;
    while (fgets(line, LENGTH, handle)) {
        line[(int) strlen(line) - 1] = 0x00;
        if (!line[0]) {
            solve(sudoku, 0, border, factor, rows, columns, boxes);
            result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2];
            index = 0;
            for (int i = 0; i < border; ++i) {
                for (int j = 0; j < border; ++j) {
                    rows[i][j] = 0;
                    columns[i][j] = 0;
                    boxes[i][j] = 0;
                }
            }
            continue;
        }

        for (int i = 0; i < border; ++i) {
            int value = line[i] - '1';
            sudoku[index][i] = value + 1;
            if (value >= 0) {
                rows[index][value] = 1;
                columns[i][value] = 1;
                boxes[index / factor * factor + i / factor][value] = 1;
            }
        }
        ++index;
        memset(line, 0x00, sizeof(char) * LENGTH);
    }
    fclose(handle);

    solve(sudoku, 0, border, factor, rows, columns, boxes);
    result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2];
    printf("%d\n", result);
}

static int solve(int **sudoku, int index, int border, int factor, int **rows, int **columns, int **boxes) {
    if (index >= border * border) {
        return 1;
    }

    int row = index / border;
    int column = index % border;
    if (sudoku[row][column]) {
        return solve(sudoku, index + 1, border, factor, rows, columns, boxes);
    }

    for (int i = 0; i < border; ++i) {
        int box_index = row / factor * factor + column / factor;
        if (!rows[row][i] && !columns[column][i] && !boxes[box_index][i]) {
            sudoku[row][column] = i + 1;
            rows[row][i] = 1;
            columns[column][i] = 1;
            boxes[box_index][i] = 1;
            if (solve(sudoku, index + 1, border, factor, rows, columns, boxes)) {
                return 1;
            }
            sudoku[row][column] = 0;
            rows[row][i] = 0;
            columns[column][i] = 0;
            boxes[box_index][i] = 0;
        }
    }
    return 0;
}
