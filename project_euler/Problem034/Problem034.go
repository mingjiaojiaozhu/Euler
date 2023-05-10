package project_euler

import (
    "fmt"
)

func Problem034() {
    factorials := make([]int, 10000)
    factorials[0] = 1
    auxiliary := make([]int, 10000)
    auxiliary[0] = 4
    for i := 1; i < 10; i++ {
        factorials[i] = factorials[i - 1] * i
        auxiliary[i] = factorials[i] + 3
    }

    result := 0
    for i := 10; i < 10000; i++ {
        factorials[i] = factorials[i / 10] + factorials[i % 10]
        if i == factorials[i] {
            result += i
        }
    }

    for i := 10; i < 100; i++ {
        auxiliary[i] = factorials[i] + 2
    }
    for i := 100; i < 1000; i++ {
        auxiliary[i] = factorials[i] + 1
    }
    for i := 1000; i < 10000; i++ {
        auxiliary[i] = factorials[i]
    }

    for i := 6 * factorials[9] + 2; i >= 10000; i-- {
        if i == getFactorialDigit(i, factorials, auxiliary) {
            result += i
        }
    }
    fmt.Println(result)
}

func getFactorialDigit(value int, factorials []int, auxiliary []int) int {
    result := 0
    for value >= 10000 {
        result += auxiliary[value % 10000]
        value /= 10000
    }
    result += factorials[value]
    return result
}
