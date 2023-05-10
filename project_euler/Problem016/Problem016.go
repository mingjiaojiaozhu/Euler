package project_euler

import (
    "fmt"
    "math"
)

func Problem016() {
    target := 1000
    length := (target + 4) / 5
    decimal := Decimal{make([]int, length), 0}
    for i := 0; i < length; i++ {
        decimal.value[i] = 0
    }
    auxiliary := make([]int, length)
    getPower(target, &decimal, auxiliary, length)

    result := 0
    for _, value := range decimal.value[:decimal.length] {
        for value > 0 {
            result += value % 10
            value /= 10
        }
    }
    fmt.Println(result)
}

func getPower(value int, decimal *Decimal, auxiliary []int, length int) {
    if value < 8 {
        decimal.value[0] = int(math.Pow(2, float64(value)))
        decimal.length = 1
        return
    }

    getPower(value >> 1, decimal, auxiliary, length)
    getSquare(decimal, auxiliary, length)
    if 0 != (value & 1) {
        getDouble(decimal)
    }
}

func getSquare(decimal *Decimal, auxiliary []int, length int) {
    for i := 0; i < length; i++ {
        auxiliary[i] = 0
    }
    for i := 0; i < decimal.length; i++ {
        for j := 0; j < decimal.length; j++ {
            result := int64(decimal.value[i] * decimal.value[j])
            index := i + j
            auxiliary[index] += int(result) % int(1e5)
            auxiliary[index + 1] += int(result) / int(1e5)
        }
    }

    decimal.length = (decimal.length << 1) - 1
    for i := 0; i < decimal.length; i++ {
        if auxiliary[i] >= int(1e5) {
            auxiliary[i + 1] += auxiliary[i] / int(1e5)
            auxiliary[i] %= int(1e5)
        }
    }
    if 0 != auxiliary[decimal.length] {
        decimal.length++
    }
    copy(decimal.value, auxiliary)
}

func getDouble(decimal *Decimal)  {
    for i := 0; i < decimal.length; i++ {
        decimal.value[i] <<= 1
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
