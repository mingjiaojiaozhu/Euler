package project_euler

import (
    "fmt"
    "math"
)

func Problem045() {
    index := int64(144)
    for true {
        hexagon := index * ((index << 1) - 1)
        if isPentagon(hexagon) {
            fmt.Println(hexagon)
            return
        }
        index++
    }
}

func isPentagon(value int64) bool {
    auxiliary := math.Sqrt(float64(value * 24 + 1))
    return math.Abs(math.Floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && 0 == (int64(auxiliary) + 1) % 6
}
