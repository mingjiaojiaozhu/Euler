package project_euler

import (
    "fmt"
    "math"
)

func Problem058() {
    target := 0.1
    index := 3
    count := 0
    for true {
        value := index * index
        for i := 0; i < 3; i++ {
            value -= index - 1
            if isPrime(value) {
                count++
            }
        }

        if float64(count) < float64((index << 1) - 1) * target {
            fmt.Println(index)
            return
        }
        index += 2
    }
}

func isPrime(value int) bool {
    if 1 != value % 6 && 5 != value % 6 {
        return 2 == value || 3 == value
    }

    border := int(math.Sqrt(float64(value)))
    for i := 5; i <= border; i += 6 {
        if 0 == value % i || 0 == value % (i + 2) {
            return false
        }
    }
    return 1 != value
}
