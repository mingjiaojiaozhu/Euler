package project_euler

import (
    "fmt"
    "math"
)

func Problem026() {
    target := 1000
    remainders := make([]int, 0)
    result := 0
    pivot := 0
    for i := target - 1; i >= 7; i -= 2 {
        if isPrime(i) {
            count := getDigit(i, remainders)
            if pivot < count {
                pivot = count
                result = i
            }
            if count == i - 1 {
                break
            }
        }
    }
    fmt.Println(result)
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

func getDigit(value int, remainders []int) int {
    remainders = []int{}
    remainder := 1
    for true {
        remainders = append(remainders, remainder)
        remainder = remainder * 10 % value
        index := find(remainder, remainders)
        if -1 != index {
            return len(remainders) - index
        }
    }
    return -1
}

func find(value int, remainders []int) int {
    for i, remainder := range remainders {
        if remainder == value {
            return i
        }
    }
    return -1
}
