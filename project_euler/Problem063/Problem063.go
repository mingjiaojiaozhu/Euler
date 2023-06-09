package project_euler

import (
    "fmt"
    "math"
)

func Problem063() {
    result := 0
    for i := 1; i < 10; i++ {
        result += int(float64(1) / (1 - math.Log10(float64(i))))
    }
    fmt.Println(result)
}
