package project_euler

import (
    "fmt"
    "math"
)

func Problem069() {
    target := 1000000
    index := 3
    result := 2
    for true {
        if isPrime(index) {
            if result * index >= target {
                fmt.Println(result)
                return
            }
            result *= index
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
