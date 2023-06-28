package project_euler

import (
    "fmt"
    "math"
)

func Problem091() {
    target := 50
    result := target * target * 3
    for i := 1; i < target; i++ {
        for j := 1; j <= target; j++ {
            divisor := commonDivisor(i, j)
            result += int(math.Min(float64((target - i) * divisor / j), float64(j * divisor / i))) << 1
        }
    }
    fmt.Println(result)
}

func commonDivisor(i int, j int) int {
    for 0 != i % j {
        i, j = j, i % j
    }
    return j
}
