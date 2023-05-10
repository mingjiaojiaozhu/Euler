package project_euler

import (
    "fmt"
    "math"
)

func Problem047() {
    target := 4
    length := 200000
    factors := make([]int, length)
    for i := 0; i < length; i++ {
        factors[i] = -1
    }

    count := 0
    for i := 2; i <= length; i++ {
        if target == getFactor(i, factors, length) {
            count++
            if target == count {
                fmt.Println(i - 3)
                return
            }
        } else {
            count = 0
        }
    }
}

func getFactor(value int, factors []int, length int) int {
    if -1 == factors[value - 1] {
        index := int64(value)
        for index <= int64(length) {
            factors[int(index) - 1] = 1
            index *= int64(value)
        }

        for i := int(math.Min(float64(value - 1), float64(length / value))); i >= 2; i-- {
            factors[value * i - 1] = factors[value - 1] + factors[i - 1]
        }
    } else {
        for i := int(math.Min(float64(value - 1), float64(length / value))); i >= 2; i-- {
            if isRelativelyPrime(value, i) && -1 == factors[value * i - 1] {
                factors[value * i - 1] = factors[value - 1] + factors[i - 1]
            }
        }
    }
    return factors[value - 1]
}

func isRelativelyPrime(i int, j int) bool {
    for 0 != i % j {
        i, j = j, i % j
    }
    return 1 == j
}
