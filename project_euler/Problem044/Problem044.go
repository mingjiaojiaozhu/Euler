package project_euler

import (
    "fmt"
    "math"
)

func Problem044() {
    pentagons := make([]int, 0)
    index := 1
    for true {
        current := index * (3 * index - 1) >> 1
        for _, pentagon := range pentagons {
            if isPentagon(current + pentagon) && isPentagon(current - pentagon) {
                fmt.Println(current - pentagon)
                return
            }
        }
        pentagons = append(pentagons, current)
        index++
    }
}

func isPentagon(value int) bool {
    delta := float64(value * 24 + 1)
    return math.Abs(math.Floor(math.Sqrt(delta) + 0.5) - math.Sqrt(delta)) < 0.00000001 && 0 == (int(math.Sqrt(delta)) + 1) % 6
}
