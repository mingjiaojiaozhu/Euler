package project_euler

import (
    "fmt"
)

func Problem032() {
    digits := make([]bool, 9)
    products := make(map[int]bool)
    for i := 1; i < 10; i++ {
        for j := 10000 / i; j >= 1234; j-- {
            getProducts(i, j, digits, products)
        }
    }

    for i := 10; i < 100; i++ {
        for j := 10000 / i; j >= 123; j-- {
            getProducts(i, j, digits, products)
        }
    }

    result := 0
    for product := range products {
        result += product
    }
    fmt.Println(result)
}

func getProducts(multiplicand int, multiplier int, digits []bool, products map[int]bool)  {
    for i := 0; i < 9; i++ {
        digits[i] = false
    }

    if isPandigital(multiplicand, digits) && isPandigital(multiplier, digits) {
        product := multiplicand * multiplier
        if isPandigital(product, digits) {
            products[product] = true
        }
    }
}

func isPandigital(value int, digits []bool) bool {
    for 0 != value {
        index := value % 10 - 1
        if index < 0 || digits[index] {
            return false
        }
        digits[index] = true
        value /= 10
    }
    return true
}
