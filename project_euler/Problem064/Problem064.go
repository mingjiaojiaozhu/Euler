package project_euler

import (
    "fmt"
    "math"
)

func Problem064() {
    target := 10000
    result := 0
    for i := 1; i <= target; i++ {
        if 0 != (getPeriod(i) & 1) {
            result++
        }
    }
    fmt.Println(result)
}

func getPeriod(value int) int {
    if math.Abs(math.Floor(math.Sqrt(float64(value)) + 0.5) - math.Sqrt(float64(value))) < 0.00000001 {
        return 0
    }

    initial := int(math.Sqrt(float64(value)))
    pivot := initial << 1
    current := initial
    offset := 0
    factor := 1
    count := 0
    for current != pivot {
        offset = current * factor - offset
        factor = (value - offset * offset) / factor
        current = (initial + offset) / factor
        count++
    }
    return count
}
