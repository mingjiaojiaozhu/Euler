import math
from typing import List

class Problem096:
    def solution(self) -> None:
        file_name, border = 'sudoku.txt', 9
        factor, sudoku = int(math.sqrt(border)), [[0 for _ in range(border)] for _ in range(border)]
        rows = [[False for _ in range(border)] for _ in range(border)]
        columns = [[False for _ in range(border)] for _ in range(border)]
        boxes = [[False for _ in range(border)] for _ in range(border)]

        result = 0
        with open(file_name, 'r') as handle:
            index = 0
            for line in handle:
                line = line.strip()
                if not line:
                    self.__solve(sudoku, 0, border, factor, rows, columns, boxes)
                    result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2]
                    index = 0
                    for i in range(border):
                        rows[i][:] = [False for _ in range(border)]
                        columns[i][:] = [False for _ in range(border)]
                        boxes[i][:] = [False for _ in range(border)]
                    continue

                for i in range(border):
                    value = int(line[i]) - 1
                    sudoku[index][i] = value + 1
                    if value >= 0:
                        rows[index][value], columns[i][value], boxes[index // factor * factor + i // factor][value] = True, True, True
                index += 1

        self.__solve(sudoku, 0, border, factor, rows, columns, boxes)
        result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2]
        print(result)

    def __solve(self, sudoku: List[List[int]], index: int, border: int, factor: int, rows: List[List[bool]], columns: List[List[bool]], boxes: List[List[bool]]) -> bool:
        if index >= border * border:
            return True

        row, column = index // border, index % border
        if sudoku[row][column]:
            return self.__solve(sudoku, index + 1, border, factor, rows, columns, boxes)

        for i in range(border):
            box_index = row // factor * factor + column // factor
            if not rows[row][i] and not columns[column][i] and not boxes[box_index][i]:
                sudoku[row][column], rows[row][i], columns[column][i], boxes[box_index][i] = i + 1, True, True, True
                if self.__solve(sudoku, index + 1, border, factor, rows, columns, boxes):
                    return True
                sudoku[row][column], rows[row][i], columns[column][i], boxes[box_index][i] = 0, False, False, False
        return False
