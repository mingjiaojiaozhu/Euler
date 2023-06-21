package project_euler

import (
    "fmt"
    "math"
)

func Problem088() {
    target := 12000
    length := int(math.Ceil(math.Log(float64(target)) / math.Log(2)))
    products := make([]int, target - 1)
    initial := int(math.Pow(2, float64(length + 1)))
    for i := target - 2; i >= 0; i-- {
        products[i] = initial
    }

    digits := make([]int, length)
    for i := 2; i < length; i++ {
        digits[i] = 1
    }
    digits[0] = 2
    digits[1] = 2

    pivot := target - length
    for true {
        product := 1
        summation := 0
        for _, value := range digits {
            product *= value
            summation += value
        }
        difference := product - summation
        if difference <= pivot {
            index := difference + length - 2
            if index >= 0 && products[index] > product {
                products[index] = product
            }
            digits[0]++
        } else {
            if !carry(digits, length) {
                break
            }
        }
    }

    result := 0
    auxiliary := make(map[int]bool)
    for _, value := range products {
        if !auxiliary[value] {
            result += value
            auxiliary[value] = true
        }
    }
    fmt.Println(result)
}

func carry(digits []int, length int) bool {
    for i := 1; i < length; i++ {
        if digits[i] != digits[i - 1] {
            digits[i]++
            value := digits[i]
            for j := 0; j < i; j++ {
                digits[j] = value
            }
            return true
        }
    }
    return false
}
