package project_euler

import (
    "fmt"
    "math"
)

func Problem010() {
    target := 2000000
    length := (target + 1) >> 1
    primes := make([]bool, length)
    primes[0] = false
    for i := 1; i < length; i++ {
        primes[i] = true
    }

    border := int(math.Sqrt(float64(target))) + 1
    for i := 3; i <= border; i += 2 {
        if primes[i >> 1] {
            for j := i * i >> 1; j < length; j += i {
                primes[j] = false
            }
        }
    }

    result := int64(2)
    for i, prime := range primes[1:] {
        if prime {
            result += int64(((i + 1) << 1) + 1)
        }
    }
    fmt.Println(result)
}
