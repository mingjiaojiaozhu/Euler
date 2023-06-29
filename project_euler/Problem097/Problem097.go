package project_euler

import (
    "fmt"
    "math"
)

func Problem097() {
    target := 7830457
    factor := 28433
    product := make([]int, 2)
    auxiliary := make([]int64, 2)
    getPower(target, product, auxiliary)
    getProduct(factor, 1, product, auxiliary)

    result := int64(product[1]) * int64(1e5) + int64(product[0])
    fmt.Println(result)
}

func getPower(value int, product []int, auxiliary []int64) {
    if value < 8 {
        product[0] = int(math.Pow(2, float64(value)))
        product[1] = 0
        return
    }

    getPower(value >> 1, product, auxiliary)
    getSquare(product, auxiliary)
    if 0 != (value & 1) {
        getDouble(product)
    }
}

func getProduct(factor int, value int, product []int, auxiliary []int64) {
    auxiliary[0] = int64(product[0]) * int64(factor) + int64(value)
    auxiliary[1] = int64(product[1]) * int64(factor)
    carry(product, auxiliary)
}

func getSquare(product []int, auxiliary []int64) {
    auxiliary[0] = int64(product[0]) * int64(product[0])
    auxiliary[1] = int64(product[0]) * int64(product[1]) << 1
    carry(product, auxiliary)
}

func getDouble(product []int) {
    product[0] <<= 1
    product[1] <<= 1
    if product[0] >= int(1e5) {
        product[1] += product[0] / int(1e5)
        product[0] %= int(1e5)
    }
    product[1] %= int(1e5)
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
