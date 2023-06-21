package project_euler

import (
    "fmt"
    "math"
)

func Problem087() {
    target := 50000000
    primes := make([][]int, 3)
    for i := 0; i < 3; i++ {
        primes[i] = make([]int, 0)
    }
    getPrimes(primes, 2, 3)

    borders := []int{int(math.Sqrt(float64(target))), int(math.Pow(float64(target), float64(1) / 3)), int(math.Pow(float64(target), float64(1) / 4))}
    index := 3
    for i := 2; i >= 0; i-- {
        size := i + 1
        for index < borders[i] {
            if isPrime(index) {
                getPrimes(primes, index, size)
            }
            index += 2
        }
    }

    summations := make(map[int]bool)
    for _, prime := range primes[2] {
        pivot := target - prime
        border := getIndex(pivot, primes[1])
        for i := 0; i < border; i++ {
            value := primes[1][i]
            end := getIndex(pivot - value, primes[0])
            for j := 0; j < end; j++ {
                summations[prime + value + primes[0][j]] = true
            }
        }
    }
    fmt.Println(len(summations))
}

func getPrimes(primes [][]int, pivot int, size int) {
    value := pivot
    for i := 0; i < size; i++ {
        value *= pivot
        primes[i] = append(primes[i], value)
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

func getIndex(value int, primes []int) int {
    start := 0
    end := len(primes) - 1
    for start <= end {
        current := start + ((end - start) >> 1)
        if primes[current] <= value {
            start = current + 1
        } else {
            end = current - 1
        }
    }
    return start
}
