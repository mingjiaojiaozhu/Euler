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
