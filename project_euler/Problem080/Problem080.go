package project_euler

import (
    "fmt"
    "math"
)

func Problem080() {
    target := 100
    current := Decimal{make([]int, 100), 0}
    auxiliary := Decimal{make([]int, 100), 0}
    for i := 0; i < 100; i++ {
        current.value[i] = 0
        auxiliary.value[i] = 0
    }
    length := (target + 2) / 5 + 1
    pivot := int(math.Pow(10, float64((target + 2) % 5)))
    result := 0
    for i := 2; i <= target; i++ {
        root := math.Sqrt(float64(i))
        if math.Abs(math.Floor(root + 0.5) - root) > 0.00000001 {
            getDigits(i, &current, &auxiliary, length, pivot)
            result += getSummation(&current)
        }
    }
    fmt.Println(result)
}

func getDigits(value int, current *Decimal, auxiliary *Decimal, length int, pivot int) {
    setValue(5, current)
    setValue(value * 5, auxiliary)
    for checkLength(current, length, pivot) {
        if !isGreater(current, auxiliary) {
            getDifference(current, auxiliary)
            current.value[0] += 10
            carry(current)
        } else {
            getProduct(auxiliary, 100)
            fillZero(current)
        }
    }
}

func getSummation(current *Decimal) int {
    result := addDigit(current.value[0] / int(1e3))
    for i := 1; i < current.length; i++ {
        result += addDigit(current.value[i])
    }
    return result
}

func setValue(value int, decimal *Decimal) {
    for i := 0; i < 100; i++ {
        decimal.value[i] = 0
    }
    decimal.value[0] = value
    decimal.length = 1
}

func checkLength(current *Decimal, length int, pivot int) bool {
    if current.length < length {
        return true
    }
    return current.value[length - 1] < pivot
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

func getDifference(decimal *Decimal, difference *Decimal) {
    for i := 0; i < decimal.length; i++ {
        difference.value[i] -= decimal.value[i]
    }

    for i := 0; i < difference.length; i++ {
        if difference.value[i] < 0 {
            difference.value[i + 1]--
            difference.value[i] += int(1e5)
        }
    }
    for 0 == difference.value[difference.length - 1] {
        difference.length--
    }
}

func getProduct(decimal *Decimal, factor int) {
    for i := 0; i < decimal.length; i++ {
        decimal.value[i] *= factor
    }
    carry(decimal)
}

func fillZero(decimal *Decimal) {
    remainder := decimal.value[0] % 10
    decimal.value[0] -= remainder
    getProduct(decimal, 10)
    decimal.value[0] += remainder
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

func addDigit(value int) int {
    result := 0
    for 0 != value {
        result += value % 10
        value /= 10
    }
    return result
}

type Decimal struct {
    value []int
    length int
}
