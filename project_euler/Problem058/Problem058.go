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
    if 0 == (value & 1) {
        return 2 == value
    }

    border := int(math.Sqrt(float64(value)))
    for i := 3; i <= border; i += 2 {
        if 0 == value % i {
            return false
        }
    }
    return 1 != value
}
