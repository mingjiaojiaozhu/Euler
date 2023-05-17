package project_euler

import (
    "fmt"
    "math"
)

func Problem057() {
    target := 1000
    numerator := Decimal{make([]int, 100), 0}
    denominator := Decimal{make([]int, 100), 0}
    for i := 0; i < 100; i++ {
        numerator.value[i] = 0
        denominator.value[i] = 0
    }
    setValue(3, &numerator)
    setValue(2, &denominator)

    result := 0
    for i := 2; i < target; i++ {
        getSummation(&denominator, &numerator)
        getSummation(&numerator, &denominator)
        swapDecimal(&numerator, &denominator)
        if numerator.length > denominator.length ||
                int(math.Log10(float64(numerator.value[numerator.length-1]))) > int(math.Log10(float64(denominator.value[denominator.length-1]))) {
            result++
        }
    }
    fmt.Println(result)
}

func setValue(value int, decimal *Decimal) {
    decimal.value[0] = value
    decimal.length = 1
}

func getSummation(decimal *Decimal, summation *Decimal) {
    for i := 0; i < decimal.length; i++ {
        summation.value[i] += decimal.value[i]
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

func swapDecimal(numerator *Decimal, denominator *Decimal) {
    length := int(math.Max(float64(numerator.length), float64(denominator.length)))
    for i := 0; i < length; i++ {
        numerator.value[i], denominator.value[i] = denominator.value[i], numerator.value[i]
    }
    numerator.length, denominator.length = denominator.length, numerator.length
}

type Decimal struct {
    value []int
    length int
}
