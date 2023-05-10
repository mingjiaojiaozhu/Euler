package project_euler

import (
    "fmt"
    "math"
)

func Problem025() {
    target := 1000
    result := int(math.Ceil((float64(target) - 1 + math.Log10(5) / 2) / math.Log10((1 + math.Sqrt(5)) / 2)))
    fmt.Println(result)
}
