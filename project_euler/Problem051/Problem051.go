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
    auxiliary := make([]int, 3)

    result := 1111
    for true {
        result = getNextPrime(result)
        if checkDigits(result, digits) && checkPrimeFamily(result, target, digits, steps, auxiliary) {
            fmt.Println(result)
            return
        }
    }
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
        combination(digit, 0, 3, &steps, auxiliary, 0)
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

func combination(digits []int, index int, count int, steps *[]int, auxiliary []int, size int) {
    if count == size {
        value := 0
        for _, digit := range auxiliary {
            value += digit
        }
        *steps = append(*steps, value)
        return
    }

    for i, value := range digits[index:] {
        auxiliary[size] = int(math.Pow(10, float64(value)))
        size++
        combination(digits, index + i + 1, count, steps, auxiliary, size)
        size--
    }
}
