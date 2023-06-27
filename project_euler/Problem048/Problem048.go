package project_euler

import (
    "fmt"
)

func Problem048() {
    target := 1000
    product := make([]int, 2)
    auxiliary := make([]int64, 2)
    result := int64(0)
    for i := target / 10 * 10 + 1; i <= target; i++ {
        getPower(i, i, product, auxiliary)
        result += int64(product[1]) * int64(1e5) + int64(product[0])
    }
    for i := target / 10 - 1; i >= 0; i-- {
        for j := 1; j < 10; j++ {
            value := i * 10 + j
            getPower(value, value, product, auxiliary)
            result += int64(product[1]) * int64(1e5) + int64(product[0])
        }
    }
    fmt.Println(result % int64(1e10))
}

func getPower(base int, index int, product []int, auxiliary []int64) {
    if 1 == index {
        product[0] = base
        product[1] = 0
        return
    }

    getPower(base, index >> 1, product, auxiliary)
    getSquare(product, auxiliary)
    if 0 != (index & 1) {
        getProduct(base, product, auxiliary)
    }
}

func getSquare(product []int, auxiliary []int64) {
    auxiliary[0] = int64(product[0]) * int64(product[0])
    auxiliary[1] = int64(product[0]) * int64(product[1]) << 1
    carry(product, auxiliary)
}

func getProduct(value int, product []int, auxiliary []int64) {
    auxiliary[0] = int64(product[0]) * int64(value)
    auxiliary[1] = int64(product[1]) * int64(value)
    carry(product, auxiliary)
}

func carry(product []int, auxiliary []int64) {
    if auxiliary[0] >= int64(1e5) {
        auxiliary[1] += auxiliary[0] / int64(1e5)
        auxiliary[0] %= int64(1e5)
    }
    auxiliary[1] %= int64(1e5)
    for i := 0; i < 2; i++ {
        product[i] = int(auxiliary[i])
    }
}
