package project_euler

import (
    "fmt"
    "math"
)

func Problem070() {
    target := 10000000
    pivot := int(math.Sqrt(float64(target)))
    start := getPreviousPrime(pivot)
    end := getNextPrime(pivot)
    primes := make([]int, 0)
    primes = append(primes, end)
    pivots := make([]int, 10)
    digits := make([]int, 10)
    result := 0
    for true {
        for _, prime := range primes {
            getDigits(start * prime, pivots)
            getDigits((start - 1) * (prime - 1), digits)
            if checkDigits(pivots, digits) {
                result = start * prime
            }
        }

        end = getNextPrime(primes[len(primes) - 1])
        for start * end < target {
            primes = append(primes, end)
            getDigits(start * end, pivots)
            getDigits((start - 1) * (end - 1), digits)
            if checkDigits(pivots, digits) {
                result = start * end
            }
            end = getNextPrime(end)
        }

        if 0 != result {
            fmt.Println(result)
            return
        }
        start = getPreviousPrime(start)
    }
}

func getPreviousPrime(value int) int {
    if 0 == (value & 1) {
        value--
    } else {
        value -= 2
    }

    for !isPrime(value) {
        value -= 2
    }
    return value
}

func getNextPrime(value int) int {
    if 0 == (value & 1) {
        value++
    } else {
        value += 2
    }

    for !isPrime(value) {
        value += 2
    }
    return value
}

func getDigits(value int, digits []int) {
    for i := 0; i < 10; i++ {
        digits[i] = 0
    }

    for 0 != value {
        digits[value % 10]++
        value /= 10
    }
}

func checkDigits(pivots []int, digits []int) bool {
    for i := 0; i < 10; i++ {
        if pivots[i] != digits[i] {
            return false
        }
    }
    return true
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
