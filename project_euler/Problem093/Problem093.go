package project_euler

import (
    "fmt"
    "math"
)

func Problem093() {
    signs := []byte{'+', '-', '*', '/'}
    operations := make([][]byte, 0)
    getOperations(signs, &operations)

    elements := []int{1, 2, 3, 4, 5, 6, 7, 8, 9}
    auxiliary := make([]float64, 4)
    result := Arithmetic{0, 0}
    calculations := make(map[int]bool)
    combination(elements, 0, 4, auxiliary, 0, operations, &result, calculations)
    fmt.Println(result.value)
}

func getOperations(signs []byte, operations *[][]byte) {
    auxiliary := make([]byte, 3)
    search(signs, 3, operations, auxiliary, 0)
}

func combination(elements []int, index int, count int, auxiliary []float64, size int, operations [][]byte, pivot *Arithmetic, calculations map[int]bool) {
    if count == size {
        calculations = make(map[int]bool)
        permutation(auxiliary, 0, count, operations, calculations)
        border := 1
        for calculations[border] {
            border++
        }
        border--
        if pivot.border < border {
            pivot.border = border
            pivot.value = 0
            for _, value := range auxiliary {
                pivot.value = pivot.value * 10 + int(value)
            }
        }
        return
    }

    for i, value := range elements[index:] {
        auxiliary[size] = float64(value)
        size++
        combination(elements, index + i + 1, count, auxiliary, size, operations, pivot, calculations)
        size--
    }
}

func search(signs []byte, count int, operations *[][]byte, auxiliary []byte, size int) {
    if count == size {
        *operations = append(*operations, make([]byte, count))
        copy((*operations)[len(*operations) - 1], auxiliary)
        return
    }

    for _, value := range signs {
        auxiliary[size] = value
        size++
        search(signs, count, operations, auxiliary, size)
        size--
    }
}

func permutation(elements []float64, index int, length int, operations [][]byte, calculations map[int]bool) {
    if index == length {
        for _, operation := range operations {
            addCalculations(calculate(operation[2], calculate(operation[1], calculate(operation[0], elements[0], elements[1]), elements[2]), elements[3]), calculations)
            addCalculations(calculate(operation[1], calculate(operation[0], elements[0], elements[1]), calculate(operation[2], elements[2], elements[3])), calculations)
            addCalculations(calculate(operation[2], calculate(operation[0], elements[0], calculate(operation[1], elements[1], elements[2])), elements[3]), calculations)
            addCalculations(calculate(operation[0], elements[0], calculate(operation[2], calculate(operation[1], elements[1], elements[2]), elements[3])), calculations)
            addCalculations(calculate(operation[0], elements[0], calculate(operation[1], elements[1], calculate(operation[2], elements[2], elements[3]))), calculations)
            addCalculations(calculate(operation[0], elements[0], calculate(operation[1], elements[1], calculate(operation[2], elements[2], elements[3]))), calculations)
        }
        return
    }

    permutation(elements, index + 1, length, operations, calculations)
    for i := index + 1; i < length; i++ {
        elements[index], elements[i] = elements[i], elements[index]
        permutation(elements, index + 1, length, operations, calculations)
        elements[index], elements[i] = elements[i], elements[index]
    }
}

func addCalculations(value float64, calculations map[int]bool) {
    if value > 0 && math.Abs(math.Floor(value + 0.5) - value) < 0.00000001 {
        calculations[int(value)] = true
    }
}

func calculate(sign byte, i float64, j float64) float64 {
    if '+' == sign {
        return i + j
    }
    if '-' == sign {
        return i - j
    }
    if '*' == sign {
        return i * j
    }
    if math.Abs(j) < 0.00000001 {
        return -1
    }
    return i / j
}

type Arithmetic struct {
    border int
    value int
}
