package project_euler

import (
    "fmt"
    "math"
)

func Problem077() {
    target := 5000
    primes := make([]int, 0)
    primes = append(primes, 2)
    primes = append(primes, 3)
    result := 11
    for getWays(result, primes) <= target {
        result++
    }
    fmt.Println(result)
}

func getWays(target int, primes []int) int {
    index := primes[len(primes) - 1] + 2
    for index <= target {
        if isPrime(index) {
            primes = append(primes, index)
        }
        index += 2
    }

    ways := make([]int, target + 1)
    for i := 1; i <= target; i++ {
        ways[i] = 0
    }
    ways[0] = 1
    for _, prime := range primes {
        for i := prime; i <= target; i++ {
            ways[i] += ways[i - prime]
        }
    }
    return ways[target]
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
