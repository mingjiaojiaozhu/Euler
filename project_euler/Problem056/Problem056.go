package project_euler

import (
    "fmt"
    "math"
)

func Problem056() {
    target := 100
    decimal := Decimal{make([]int, target), 0}
    for i := 0; i < target; i++ {
        decimal.value[i] = 0
    }
    result := 0
    for i := 2; i < target; i++ {
        for j := 0; j < target; j++ {
            decimal.value[j] = 0
        }
        setValue(i, &decimal)
        for j := 2; j < target; j++ {
            getProduct(i, &decimal)
            result = getDigital(&decimal, result)
        }
    }
    fmt.Println(result)
}

func setValue(value int, decimal *Decimal) {
    decimal.value[0] = value
    decimal.length = 1
}

func getProduct(value int, decimal *Decimal) {
    for i := 0; i < decimal.length; i++ {
        decimal.value[i] *= value
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

func getDigital(decimal *Decimal, pivot int) int {
    result := 0
    for _, value := range decimal.value[:decimal.length] {
        for 0 != value {
            result += value % 10
            value /= 10
        }
    }
    return int(math.Max(float64(result), float64(pivot)))
}

type Decimal struct {
    value []int
    length int
}
