package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "math"
    "os"
    "strings"
)

func Problem096() {
    fileName := "sudoku.txt"
    border := 9
    factor := int(math.Sqrt(float64(border)))
    sudoku := make([][]int, border)
    rows := make([][]bool, border)
    columns := make([][]bool, border)
    boxes := make([][]bool, border)
    for i := 0; i < border; i++ {
        sudoku[i] = make([]int, border)
        rows[i] = make([]bool, border)
        columns[i] = make([]bool, border)
        boxes[i] = make([]bool, border)
        for j := 0; j < border; j++ {
            rows[i][j] = false
            columns[i][j] = false
            boxes[i][j] = false
        }
    }

    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    index := 0
    result := 0
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        elements := strings.Replace(string(line), "\n", "", -1)
        if "" == elements {
            solve(sudoku, 0, border, factor, rows, columns, boxes)
            result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2]
            index = 0
            for i := 0; i < border; i++ {
                for j := 0; j < border; j++ {
                    rows[i][j] = false
                    columns[i][j] = false
                    boxes[i][j] = false
                }
            }
            continue
        }

        for i := 0; i < border; i++ {
            value := int(elements[i] - '0') - 1
            sudoku[index][i] = value + 1
            if value >= 0 {
                rows[index][value] = true
                columns[i][value] = true
                boxes[index / factor * factor + i / factor][value] = true
            }
        }
        index++
    }
    file.Close()

    solve(sudoku, 0, border, factor, rows, columns, boxes)
    result += sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2]
    fmt.Println(result)
}

func solve(sudoku [][]int, index int, border int, factor int, rows [][]bool, columns [][]bool, boxes [][]bool) bool {
    if index >= border * border {
        return true
    }

    row := index / border
    column := index % border
    if 0 != sudoku[row][column] {
        return solve(sudoku, index + 1, border, factor, rows, columns, boxes)
    }

    for i := 0; i < border; i++ {
        boxIndex := row / factor * factor + column / factor
        if !rows[row][i] && !columns[column][i] && !boxes[boxIndex][i] {
            sudoku[row][column] = i + 1
            rows[row][i] = true
            columns[column][i] = true
            boxes[boxIndex][i] = true
            if solve(sudoku, index + 1, border, factor, rows, columns, boxes) {
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
