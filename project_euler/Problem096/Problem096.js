function Problem096() {
    let fileName = 'sudoku.txt'
    let border = 9
    let factor = Math.floor(Math.sqrt(border))
    let sudoku = Array(border)
    let rows = Array(border)
    let columns = Array(border)
    let boxes = Array(border)
    for (let i = 0; i < border; ++i) {
        sudoku[i] = Array(border)
        rows[i] = Array(border).fill(false)
        columns[i] = Array(border).fill(false)
        boxes[i] = Array(border).fill(false)
    }

    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    let index = 0
    let result = 0
    while (line = handle.next()) {
        let elements = line.toString()
        if (!elements) {
            solve(sudoku, 0, border, factor, rows, columns, boxes)
            result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2]
            index = 0
            for (let i = 0; i < border; ++i) {
                rows[i].fill(false)
                columns[i].fill(false)
                boxes[i].fill(false)
            }
            continue
        }

        for (let i = 0; i < border; ++i) {
            let value = elements[i] - '1'
            sudoku[index][i] = value + 1
            if (value >= 0) {
                rows[index][value] = true
                columns[i][value] = true
                boxes[Math.floor(index / factor) * factor + Math.floor(i / factor)][value] = true
            }
        }
        ++index
    }

    solve(sudoku, 0, border, factor, rows, columns, boxes)
    result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2]
    console.log(result)
}

function solve(sudoku, index, border, factor, rows, columns, boxes) {
    if (index >= border * border) {
        return true
    }

    let row = Math.floor(index / border)
    let column = index % border
    if (sudoku[row][column]) {
        return solve(sudoku, index + 1, border, factor, rows, columns, boxes)
    }

    for (let i = 0; i < border; ++i) {
        let boxIndex = Math.floor(row / factor) * factor + Math.floor(column / factor)
        if (!rows[row][i] && !columns[column][i] && !boxes[boxIndex][i]) {
            sudoku[row][column] = i + 1
            rows[row][i] = true
            columns[column][i] = true
            boxes[boxIndex][i] = true
            if (solve(sudoku, index + 1, border, factor, rows, columns, boxes)) {
                return true
            }
            sudoku[row][column] = 0
            rows[row][i] = false
            columns[column][i] = false
            boxes[boxIndex][i] = false
        }
    }
    return false
}

module.exports = {
    Problem096 : Problem096
};
