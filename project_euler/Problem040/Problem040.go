package project_euler

import (
    "fmt"
    "math"
)

func Problem040() {
    target := 1000000
    borders := make([]int, 0)
    index := 0
    for true {
        value := (int(math.Pow(10, float64(index)))*(9*index-1) + 1) / 9
        borders = append(borders, value)
        if value > target {
            break
        }
        index++
    }

    result := 1
    for 0 != target {
        result *= getChampernowne(target, borders)
        target /= 10
    }
    fmt.Println(result)
}

func getChampernowne(value int, borders []int) int {
    index := getIndex(value, borders) - 1
    value -= borders[index] + 1
    digit := int(math.Pow(10, float64(index))) + value / (index + 1)
    for i := value % (index + 1); i < index; i++ {
        digit /= 10
    }
    return digit % 10
}

func getIndex(value int, borders []int) int {
    start := 0
    end := len(borders) - 1
    for start <= end {
        current := start + ((end - start) >> 1)
        if borders[current] <= value {
            start = current + 1
        } else {
            end = current - 1
        }
    }
    return start
}
