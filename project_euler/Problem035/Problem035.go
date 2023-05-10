package project_euler

import (
    "fmt"
    "math"
)

func Problem035() {
    target := 1000000
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

    result := 13
    for i := 101; i < target; i += 2 {
        if primes[i >> 1] && checkDigits(i) && isCircular(i, primes) {
            result++
        }
    }
    fmt.Println(result)
}

func checkDigits(value int) bool {
    for 0 != value {
        remainder := value % 10
        if 1 != remainder && 3 != remainder && 7 != remainder && 9 != remainder {
            return false
        }
        value /= 10
    }
    return true
}

func isCircular(value int, primes []bool) bool {
    divisor := 1
    length := 1
    for value / divisor >= 10 {
        divisor *= 10
        length++
    }

    for i := 1; i < length; i++ {
        value = (value % 10) * divisor + value / 10
        if !primes[value >> 1] {
            return false
        }
    }
    return true
}
