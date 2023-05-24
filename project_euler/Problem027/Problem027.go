package project_euler

import (
    "fmt"
    "math"
)

func Problem027() {
    target := 1000
    border := -1 * (target - 1)
    result := 0
    pivot := 0
    for i := 3; i < target; i += 2 {
        if !isPrime(i) {
            continue
        }

        for j := border; j < target; j += 2 {
            count := 1
            for isPrime(count * count + count * j + i) {
                count++
            }
            if pivot < count {
                pivot = count
                result = i * j
            }
        }
    }
    fmt.Println(result)
}

func isPrime(value int) bool {
    if value <= 0 {
        return false
    }
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
