package project_euler

import (
    "fmt"
    "math"
)

func Problem037() {
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

    result := 0
    for i := 11; i < target; i += 2 {
        if primes[i >> 1] && checkDigits(i) && isTruncatable(i, primes) {
            result += i
        }
    }
    fmt.Println(result)
}

func checkDigits(value int) bool {
    remainder := value % 10
    if 3 != remainder && 7 != remainder {
        return false
    }

    value /= 10
    for value >= 10 {
        remainder = value % 10
        if 1 != remainder && 3 != remainder && 7 != remainder && 9 != remainder {
            return false
        }
        value /= 10
    }
    return 2 == value || 3 == value || 5 == value || 7 == value
}

func isTruncatable(value int, primes []bool) bool {
    divisor := 1
    for value / divisor >= 10 {
        divisor *= 10
    }

    head := value / 10
    tail := value % divisor
    for 0 != head && 0 != tail {
        if (2 != head && !primes[head >> 1]) || !primes[tail >> 1] {
            return false
        }

        divisor /= 10
        head /= 10
        tail %= divisor
    }
    return true
}
