package project_euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Problem096 {
    public void solution() throws IOException {
        String fileName = "sudoku.txt";
        int border = 9;
        int factor = (int) Math.sqrt(border);
        int[][] sudoku = new int[border][border];
        boolean[][] rows = new boolean[border][border];
        boolean[][] columns = new boolean[border][border];
        boolean[][] boxes = new boolean[border][border];
        for (int i = 0; i < border; ++i) {
            Arrays.fill(rows[i], false);
            Arrays.fill(columns[i], false);
            Arrays.fill(boxes[i], false);
        }

        int result = 0;
        try (BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            int index = 0;
            while (null != (line = handle.readLine())) {
                if (line.isEmpty()) {
                    solve(sudoku, 0, border, factor, rows, columns, boxes);
                    result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2];
                    index = 0;
                    for (int i = 0; i < border; ++i) {
                        Arrays.fill(rows[i], false);
                        Arrays.fill(columns[i], false);
                        Arrays.fill(boxes[i], false);
                    }
                    continue;
                }

                for (int i = 0; i < border; ++i) {
                    int value = line.charAt(i) - '1';
                    sudoku[index][i] = value + 1;
                    if (value >= 0) {
                        rows[index][value] = true;
                        columns[i][value] = true;
                        boxes[index / factor * factor + i / factor][value] = true;
                    }
                }
                ++index;
            }
        }

        solve(sudoku, 0, border, factor, rows, columns, boxes);
        result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2];
        System.out.println(result);
    }

    private boolean solve(int[][] sudoku, int index, int border, int factor, boolean[][] rows, boolean[][] columns, boolean[][] boxes) {
        if (index >= border * border) {
            return true;
        }

        int row = index / border;
        int column = index % border;
        if (0 != sudoku[row][column]) {
            return solve(sudoku, index + 1, border, factor, rows, columns, boxes);
        }

        for (int i = 0; i < border; ++i) {
            int boxIndex = row / factor * factor + column / factor;
            if (!rows[row][i] && !columns[column][i] && !boxes[boxIndex][i]) {
                sudoku[row][column] = i + 1;
                rows[row][i] = true;
                columns[column][i] = true;
                boxes[boxIndex][i] = true;
                if (solve(sudoku, index + 1, border, factor, rows, columns, boxes)) {
                    return true;
                }
                sudoku[row][column] = 0;
                rows[row][i] = false;
                columns[column][i] = false;
                boxes[boxIndex][i] = false;
            }
        }
        return false;
    }
}
