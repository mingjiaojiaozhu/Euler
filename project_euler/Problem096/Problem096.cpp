#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class Problem096 {
public:
    void solution() {
        string file_name = "sudoku.txt";
        int border = 9;
        int factor = (int) sqrt(border);
        vector<vector<int>> sudoku(border, vector<int>(border));
        vector<vector<bool>> rows(border, vector<bool>(border, false));
        vector<vector<bool>> columns(border, vector<bool>(border, false));
        vector<vector<bool>> boxes(border, vector<bool>(border, false));

        fstream handle(file_name, ios::in);
        string line;
        int index = 0;
        int result = 0;
        while (getline(handle, line)) {
            if (line.empty()) {
                solve(sudoku, 0, border, factor, rows, columns, boxes);
                result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2];
                index = 0;
                for (int i = 0; i < border; ++i) {
                    rows[i].assign(border, false);
                    columns[i].assign(border, false);
                    boxes[i].assign(border, false);
                }
                continue;
            }

            for (int i = 0; i < border; ++i) {
                int value = line[i] - '1';
                sudoku[index][i] = value + 1;
                if (value >= 0) {
                    rows[index][value] = true;
                    columns[i][value] = true;
                    boxes[index / factor * factor + i / factor][value] = true;
                }
            }
            ++index;
        }
        handle.close();

        solve(sudoku, 0, border, factor, rows, columns, boxes);
        result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2];
        cout << result << endl;
    }

private:
    bool solve(vector<vector<int>> &sudoku, int index, int border, int factor, vector<vector<bool>> &rows, vector<vector<bool>> &columns, vector<vector<bool>> &boxes) {
        if (index >= border * border) {
            return true;
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
                rows[row][i] = true;
                columns[column][i] = true;
                boxes[box_index][i] = true;
                if (solve(sudoku, index + 1, border, factor, rows, columns, boxes)) {
                    return true;
                }
                sudoku[row][column] = 0;
                rows[row][i] = false;
                columns[column][i] = false;
                boxes[box_index][i] = false;
            }
        }
        return false;
    }
};
