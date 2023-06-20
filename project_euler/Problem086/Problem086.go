package project_euler

import (
    "fmt"
    "math"
)

func Problem086() {
    target := 1000000
    count := 0
    result := 1
    for count < target {
        result++
        for i := 3; i < result; i++ {
            root := math.Sqrt(float64(result * result + i * i))
            if math.Abs(math.Floor(root + 0.5) - root) < 0.00000001 {
                count += i >> 1
            }
        }
        for i := (result << 1) - 1; i >= result; i-- {
            root := math.Sqrt(float64(result * result + i * i))
            if math.Abs(math.Floor(root + 0.5) - root) < 0.00000001 {
                count += result - ((i + 1) >> 1) + 1
            }
        }
    }
    fmt.Println(result)
}
