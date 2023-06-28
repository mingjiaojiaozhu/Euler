package project_euler

import (
    "fmt"
    "math"
)

func Problem092() {
    target := 10000000
    border := 9 * 9 * int(math.Log10(float64(target)))
    chains := make(map[int]bool)
    pivot := 89
    chains[pivot] = true

    squares := make([]int, 10)
    for i := 0; i < 10; i++ {
        squares[i] = i * i
    }

    result := 0
    for i := 1; i <= border; i++ {
        if getChains(i, chains, pivot, squares) {
            result++
        }
    }
    for i := border + 1; i < target; i++ {
        if chains[squareDigits(i, squares)] {
            result++
        }
    }
    fmt.Println(result)
}

func getChains(value int, chains map[int]bool, pivot int, squares []int) bool {
    if chains[value] || pivot == value {
        return true
    }
    if 1 == value {
        return false
    }

    result := getChains(squareDigits(value, squares), chains, pivot, squares)
    if result {
        chains[value] = true
    }
    return result
}

func squareDigits(value int, squares []int) int {
    result := 0
    for 0 != value {
        result += squares[value % 10]
        value /= 10
    }
    return result
}
