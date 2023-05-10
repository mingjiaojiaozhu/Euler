package project_euler

import (
    "fmt"
    "math"
)

func Problem007() {
    target := 10001
    result := 1
    count := 1
    for count < target {
        result += 2
        if isPrime(result) {
            count++
        }
    }
    fmt.Println(result)
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
