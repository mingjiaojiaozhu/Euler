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
    auxiliary := math.Sqrt(float64(value))
    if math.Abs(math.Floor(auxiliary + 0.5) - auxiliary) < 0.00000001 {
        return 0
    }

    initial := int(auxiliary)
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
