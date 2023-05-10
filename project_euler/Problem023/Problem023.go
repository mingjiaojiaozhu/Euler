package project_euler

import (
    "fmt"
    "math"
)

func Problem023() {
    start := 24
    end := 28123
    abundants := map[int]bool{}
    for i := start >> 1; i <= start; i++ {
        if isAbundant(i) {
            abundants[i] = true
        }
    }

    result := start * (start - 1) >> 1
    for i := start + 1; i <= end; i++ {
        isNonAbundant := true
        for abundant := range abundants {
            if abundants[i - abundant] {
                isNonAbundant = false
                break
            }
        }
        if isNonAbundant {
            result += i
        }

        if isAbundant(i) {
            abundants[i] = true
        }
    }
    fmt.Println(result)
}

func isAbundant(value int) bool {
    border := int(math.Sqrt(float64(value)))
    summation := 1
    for i := 2; i < border; i++ {
        if 0 == value % i {
            summation += i + value / i
        }
    }
    if 0 == value % border {
        summation += border
        if value != border * border {
            summation += value / border
        }
    }
    return summation > value
}
