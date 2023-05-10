package project_euler

import (
    "fmt"
    "math"
)

func Problem046() {
    primes := make(map[int]bool)
    primes[2] = true
    result := 3
    for true {
        if isPrime(result) {
            primes[result] = true
        } else {
            border := int(math.Sqrt(float64((result - 1) >> 1)))
            isGoldbach := false
            for i := 1; i <= border; i++ {
                if primes[result - (i * i << 1)] {
                    isGoldbach = true
                    break
                }
            }
            if !isGoldbach {
                fmt.Println(result)
                return
            }
        }
        result += 2
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
