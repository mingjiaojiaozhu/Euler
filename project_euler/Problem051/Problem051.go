package project_euler

import (
    "fmt"
    "math"
)

func Problem051() {
    target := 8
    digits := make([][]int, 3)
    for i :=0; i < 3; i++ {
        digits[i] = make([]int, 0)
    }
    steps := make([]int, 0)
    auxiliary := make([]int, 0)

    index := 1111
    for true {
        prime := getNextPrime(index)
        if checkDigits(prime, digits) && checkPrimeFamily(prime, target, digits, steps, auxiliary) {
            fmt.Println(prime)
            return
        }
        index = prime + 1
    }
}

func getNextPrime(value int) int {
    if 0 == (value & 1) {
        value++
    }

    for !isPrime(value) {
        value += 2
    }
    return value
}

func checkDigits(value int, digits [][]int) bool {
    for i := 0; i < 3; i++ {
        digits[i] = make([]int, 0)
    }

    value /= 10
    count := 1
    for 0 != value {
        remainder := value % 10
        if 0 == remainder || 1 == remainder || 2 == remainder {
            digits[remainder] = append(digits[remainder], count)
        }
        value /= 10
        count++
    }

    for _, digit := range digits {
        if len(digit) >= 3 {
            return true
        }
    }
    return false
}

func checkPrimeFamily(pivot int, target int, digits [][]int, steps []int, auxiliary []int) bool {
    isFamily := false
    for i, digit := range digits {
        if len(digit) < 3 {
            continue
        }

        steps = make([]int, 0)
        auxiliary = make([]int, 0)
        combination(digit, 0, 3, len(digit), &steps, auxiliary)
        for _, step := range steps {
            count := 10 - target - i
            value := pivot
            for j := i; j < 9; j++ {
                value += step
                if !isPrime(value) {
                    count--
                }
                if count < 0 {
                    break
                }
            }
            isFamily = 0 == count
        }
    }
    return isFamily
}

func combination(digits []int, start int, count int, length int, steps *[]int, auxiliary []int) {
    if count == len(auxiliary) {
        value := 0
        for _, digit := range auxiliary {
            value += digit
        }
        *steps = append(*steps, value)
        return
    }

    for i := start; i < length; i++ {
        auxiliary = append(auxiliary, int(math.Pow(10, float64(digits[i]))))
        combination(digits, i + 1, count, length, steps, auxiliary)
        auxiliary = auxiliary[:len(auxiliary) - 1]
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
