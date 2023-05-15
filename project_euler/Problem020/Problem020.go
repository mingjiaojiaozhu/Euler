package project_euler

import "fmt"

func Problem020() {
    target := 100
    decimal := Decimal{make([]int, target), 0}
    for i := 0; i < target; i++ {
        decimal.value[i] = 0
    }
    decimal.value[0] = target
    decimal.length = 1

    for i := target - 1; i > 1; i-- {
        getProduct(i, &decimal)
    }

    result := 0
    for _, value := range decimal.value[:decimal.length] {
        for 0 != value {
            result += value % 10
            value /= 10
        }
    }
    fmt.Println(result)
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

type Decimal struct {
    value []int
    length int
}
