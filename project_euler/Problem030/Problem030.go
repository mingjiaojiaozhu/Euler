package project_euler

import (
    "fmt"
    "math"
)

func Problem030() {
    target := 5
    powers := make([]int, 10)
    for i := 0; i < 10; i++ {
        powers[i] = int(math.Pow(float64(i), float64(target)))
    }

    result := 0
    for i := 6 * powers[9]; i >= 10; i-- {
        if i == getPowerDigit(i, powers) {
            result += i
        }
    }
    fmt.Println(result)
}

func getPowerDigit(value int, powers []int) int {
    result := 0
    for 0 != value {
        result += powers[value % 10]
        value /= 10
    }
    return result
}
