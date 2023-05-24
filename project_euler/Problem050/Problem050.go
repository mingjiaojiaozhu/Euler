package project_euler

import (
    "fmt"
    "math"
)

func Problem050() {
    target := 1000000
    primes := make([]int, 0)
    primes = append(primes, 2)
    index := 3
    summation := 2
    for summation < target {
        if isPrime(index) {
            primes = append(primes, index)
            summation += index
        }
        index += 2
    }

    length := len(primes)
    for i := length - 1; i > 0; i-- {
        value := summation - primes[i]
        if isPrime(value) {
            fmt.Println(value)
            return
        }
        summation = value

        for j := i; j < length; j++ {
            value += primes[j] - primes[j - i]
            if isPrime(value) && value < target {
                fmt.Println(value)
                return
            }
        }
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
