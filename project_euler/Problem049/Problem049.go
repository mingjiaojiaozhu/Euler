package project_euler

import (
    "fmt"
    "math"
)

func Problem049() {
    target := 3330
    other := 1487
    terms := make([]int, 2)
    digits := make([]bool, 10)
    for i := 10000 - (target << 1) - 1; i > 1000; i -= 2 {
        if isPrime(i) && i != other {
            terms[0] = i + target
            terms[1] = terms[0] + target
            if isPrime(terms[0]) && isPrime(terms[1]) && checkDigit(i, terms, digits) {
                fmt.Printf("%d%d%d\n", i, terms[0], terms[1])
                return
            }
        }
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

func checkDigit(value int, terms []int, digits []bool) bool {
    for i := 0; i < 10; i++ {
        digits[i] = false
    }
    for 0 != value {
        digits[value % 10] = true
        value /= 10
    }

    for _, term := range terms {
        for 0 != term {
            if !digits[term % 10] {
                return false
            }
            term /= 10
        }
    }
    return true
}
