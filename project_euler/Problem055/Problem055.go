package project_euler

import (
    "fmt"
    "math"
)

func Problem055() {
    target := 10000
    decimal := Decimal{make([]int, 100), 0}
    for i := 0; i < 100; i++ {
        decimal.value[i] = 0
    }
    auxiliary := make([]int, 100)
    result := 0
    for i := 1; i < target; i++ {
        if isLychrel(i, &decimal, auxiliary) {
            result++
        }
    }
    fmt.Println(result)
}

func isLychrel(value int, decimal *Decimal, auxiliary []int) bool {
    setValue(value, decimal)
    reverseValue(decimal, auxiliary)
    getSummation(decimal, auxiliary)

    count := 0
    for count < 50 {
        reverseValue(decimal, auxiliary)
        if isEqual(decimal, auxiliary) {
            return false
        }
        getSummation(decimal, auxiliary)
        count++
    }
    return true
}

func setValue(value int, decimal *Decimal) {
    for i := 0; i < 100; i++ {
        decimal.value[i] = 0
    }
    decimal.length = 0
    for 0 != value {
        decimal.value[decimal.length] = value % int(1e5)
        decimal.length++
        value /= int(1e5)
    }
}

func reverseValue(decimal *Decimal, auxiliary []int) {
    for i := 0; i < 100; i++ {
        auxiliary[i] = 0
    }

    index := 0
    count := 0
    for i := decimal.length - 1; i >= 0; i-- {
        value := decimal.value[i]
        divisor := int(1e5) / 10
        if i == decimal.length - 1 {
            for 0 == value / divisor {
                divisor /= 10
            }
        }
        for 0 != divisor {
            auxiliary[index] += (value / divisor) * int(math.Pow(10, float64(count)))
            value %= divisor
            divisor /= 10
            count++
            if 5 == count {
                index++
                count = 0
            }
        }
    }
}

func getSummation(decimal *Decimal, auxiliary []int) {
    for i := 0; i < decimal.length; i++ {
        decimal.value[i] += auxiliary[i]
    }

    for i := 0; i < decimal.length; i++ {
        if decimal.value[i] >= int(1e5) {
            decimal.value[i + 1] += decimal.value[i] / int(1e5)
            decimal.value[i] %= int(1e5)
        }
    }
    if 0 != decimal.value[decimal.length] {
        decimal.length++
    }
}

func isEqual(decimal *Decimal, auxiliary []int) bool {
    for i := 0; i < decimal.length; i++ {
        if decimal.value[i] != auxiliary[i] {
            return false
        }
    }
    return true
}

type Decimal struct {
    value []int
    length int
}
