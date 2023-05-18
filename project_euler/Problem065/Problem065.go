package project_euler

import (
    "fmt"
    "math"
)

func Problem065() {
    target := 100
    previous := Decimal{make([]int, 100), 0}
    current := Decimal{make([]int, 100), 0}
    setValue(1, &previous)
    setValue(2, &current)
    for i := 2; i <= target; i++ {
        factor := 1
        if 0 == i % 3 {
            factor = (i << 1) / 3
        }
        getSummation(&current, factor, &previous)
        swapDecimal(&previous, &current)
    }

    result := 0
    for _, value := range current.value[:current.length] {
        for 0 != value {
            result += value % 10
            value /= 10
        }
    }
    fmt.Println(result)
}

func setValue(value int, decimal *Decimal) {
    decimal.value[0] = value
    decimal.length = 1
}

func getSummation(decimal *Decimal, factor int, summation *Decimal) {
    for i := 0; i < decimal.length; i++ {
        summation.value[i] += decimal.value[i] * factor
    }

    for i := 0; i < summation.length; i++ {
        if summation.value[i] >= int(1e5) {
            summation.value[i + 1] += summation.value[i] / int(1e5)
            summation.value[i] %= int(1e5)
        }
    }
    if 0 != summation.value[summation.length] {
        summation.length++
    }
}

func swapDecimal(previous *Decimal, current *Decimal) {
    length := int(math.Max(float64(previous.length), float64(current.length)))
    for i := 0; i < length; i++ {
        previous.value[i], current.value[i] = current.value[i], previous.value[i]
    }
    previous.length, current.length = current.length, previous.length
}

type Decimal struct {
    value []int
    length int
}
