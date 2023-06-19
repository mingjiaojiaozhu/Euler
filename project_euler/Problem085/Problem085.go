package project_euler

import (
    "fmt"
    "math"
)

func Problem085() {
    target := 2000000
    border := int(math.Sqrt(1 + 8 * math.Sqrt(float64(target))) - 1) >> 1
    result := 0
    pivot := target
    for i := 1; i <= border; i++ {
        length := int(math.Sqrt(1 + float64(target << 4) / float64(i) / float64(i + 1)) - 1) >> 1
        value := int(math.Min(math.Abs(float64(getCount(length, i) - target)), math.Abs(float64(getCount(length + 1, i) - target))))
        if pivot > value {
            result = length * i
            pivot = value
        }
    }
    fmt.Println(result)
}

func getCount(length int, width int) int {
    return length * (length + 1) * width * (width + 1) >> 2
}
