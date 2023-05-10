package project_euler

import (
    "fmt"
)

func Problem048() {
    target := 1000
    product := make([]int64, 2)
    auxiliary := make([]int64, 2)
    result := int64(0)
    for i := 1; i <= target; i++ {
        if 0 != i % 10 {
            getPower(i, i, product, auxiliary)
            result += product[1] * int64(1e5) + product[0]
        }
    }
    fmt.Println(result % int64(1e10))
}

func getPower(base int, index int, product []int64, auxiliary []int64) {
    if 1 == index {
        product[0] = int64(base)
        product[1] = int64(0)
        return
    }

    getPower(base, index >> 1, product, auxiliary)
    getSquare(product, auxiliary)
    if 0 != (index & 1) {
        getProduct(base, product)
    }
}

func getSquare(product []int64, auxiliary []int64) {
    auxiliary[0] = product[0] * product[0]
    auxiliary[1] = product[0] * product[1] + product[1] * product[0]
    if auxiliary[0] >= int64(1e5) {
        auxiliary[1] += auxiliary[0] / int64(1e5)
        auxiliary[0] %= int64(1e5)
    }
    auxiliary[1] %= int64(1e5)
    copy(product, auxiliary)
}

func getProduct(value int, product []int64)  {
    product[0] *= int64(value)
    product[1] *= int64(value)
    if product[0] >= int64(1e5) {
        product[1] += product[0] / int64(1e5)
        product[0] %= int64(1e5)
    }
    product[1] %= int64(1e5)
}
