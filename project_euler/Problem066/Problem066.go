package project_euler

import (
    "fmt"
    "math"
)

func Problem066() {
    target := 1000
    factors := make([]int, 0)
    previous := Decimal{make([]int, 100), 0}
    current := Decimal{make([]int, 100), 0}
    auxiliary := Decimal{make([]int, 100), 0}

    result := 0
    pivot := Decimal{make([]int, 100), 0}
    for i := 5; i <= target; i++ {
        if getSolution(i, factors, &previous, &current, &auxiliary) && isGreater(&current, &pivot) {
            swapDecimal(&current, &pivot)
            result = i
        }
    }
    fmt.Println(result)
}

func getSolution(value int, factors []int, previous *Decimal, current *Decimal, auxiliary *Decimal) bool {
    factors = make([]int, 0)
    start := getPeriod(value, &factors)
    if 0 == start {
        return false
    }

    setValue(0, previous)
    setValue(1, current)
    getConvergents(previous, current, factors)
    if 0 != (len(factors) & 1) {
        return true
    }

    setValue(1, previous)
    setValue(start, auxiliary)
    getConvergents(previous, auxiliary, factors)
    swapDecimal(previous, current)
    getProduct(previous, auxiliary, current)
    getDouble(current)
    return true
}

func isGreater(current *Decimal, pivot *Decimal) bool {
    if current.length != pivot.length {
        return current.length > pivot.length
    }

    for i := current.length - 1; i >= 0; i-- {
        if current.value[i] != pivot.value[i] {
            return current.value[i] > pivot.value[i]
        }
    }
    return false
}

func swapDecimal(previous *Decimal, current *Decimal) {
    length := int(math.Max(float64(previous.length), float64(current.length)))
    for i := 0; i < length; i++ {
        previous.value[i], current.value[i] = current.value[i], previous.value[i]
    }
    previous.length, current.length = current.length, previous.length
}

func getPeriod(value int, factors *[]int) int {
    if math.Abs(math.Floor(math.Sqrt(float64(value)) + 0.5) - math.Sqrt(float64(value))) < 0.00000001 {
        return 0
    }

    initial := int(math.Sqrt(float64(value)))
    pivot := initial << 1
    current := initial
    offset := 0
    factor := 1
    for current != pivot {
        offset = current * factor - offset
        factor = (value - offset * offset) / factor
        current = (initial + offset) / factor
        *factors = append(*factors, current)
    }
    *factors = (*factors)[:len(*factors) - 1]
    return initial
}

func setValue(value int, decimal *Decimal) {
    for i := 0; i < 100; i++ {
        decimal.value[i] = 0
    }
    decimal.value[0] = value
    decimal.length = 1
}

func getConvergents(previous *Decimal, current *Decimal, factors []int) {
    for _, factor := range factors {
        getSummation(current, factor, previous)
        swapDecimal(previous, current)
    }
}

func getProduct(multiplicand *Decimal, multiplier *Decimal, product *Decimal) {
    for i := 0; i < multiplicand.length; i++ {
        for j := 0; j < multiplier.length; j++ {
            value := int64(multiplicand.value[i]) * int64(multiplier.value[j])
            index := i + j
            product.value[index] += int(value % int64(1e5))
            product.value[index + 1] += int(value / int64(1e5))
        }
    }
    product.length = multiplicand.length + multiplier.length - 1
    carry(product)
}

func getDouble(decimal *Decimal)  {
    for i := 0; i < decimal.length; i++ {
        decimal.value[i] <<= 1
    }
    carry(decimal)
}

func getSummation(decimal *Decimal, factor int, summation *Decimal) {
    for i := 0; i < decimal.length; i++ {
        summation.value[i] += decimal.value[i] * factor
    }
    carry(summation)
}

func carry(decimal *Decimal) {
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
