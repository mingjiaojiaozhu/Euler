package project_euler

import "fmt"

func Problem011() {
    target := [][]int{{8, 2, 22, 97, 38, 15, 0, 40, 0, 75, 4, 5, 7, 78, 52, 12, 50, 77, 91, 8},
            {49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4, 56, 62, 0},
            {81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3, 49, 13, 36, 65},
            {52, 70, 95, 23, 4, 60, 11, 42, 69, 24, 68, 56, 1, 32, 56, 71, 37, 2, 36, 91},
            {22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80},
            {24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50},
            {32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70},
            {67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21},
            {24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72},
            {21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33, 95},
            {78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56, 92},
            {16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85, 57},
            {86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58},
            {19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55, 40},
            {4, 52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66},
            {88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69},
            {4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36},
            {20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4, 36, 16},
            {20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5, 54},
            {1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67, 48}}
    size := 4
    length := len(target)

    product := Product{1, 0, 0}
    result := calculateRow(target, length, size, &product, 0)
    result = calculateColumn(target, length, size, &product, result)
    result = calculateDiagonalLeft(target, length, size, &product, result)
    result = calculateDiagonalRight(target, length, size, &product, result)
    fmt.Println(result)
}

func calculateRow(target [][]int, length int, size int, product *Product, pivot int) int {
    for i := 0; i < length; i++ {
        product.value = 1
        product.indexRow = i
        product.indexColumn = 0
        multiplyRow(target, length, size, product)
        if pivot < product.value {
            pivot = product.value
        }

        for product.indexColumn < length {
            value := target[product.indexRow][product.indexColumn]
            if 0 != value {
                product.value = product.value / target[product.indexRow][product.indexColumn - size] * value
                product.indexColumn++
            } else {
                product.value = 1
                product.indexColumn++
                multiplyRow(target, length, size, product)
            }
            if pivot < product.value {
                pivot = product.value
            }
        }
    }
    return pivot
}

func calculateColumn(target [][]int, length int, size int, product *Product, pivot int) int {
    for i := 0; i < length; i++ {
        product.value = 1
        product.indexRow = 0
        product.indexColumn = i
        multiplyColumn(target, length, size, product)
        if pivot < product.value {
            pivot = product.value
        }

        for product.indexRow < length {
            value := target[product.indexRow][product.indexColumn]
            if 0 != value {
                product.value = product.value / target[product.indexRow - size][product.indexColumn] * value
                product.indexRow++
            } else {
                product.value = 1
                product.indexRow++
                multiplyColumn(target, length, size, product)
            }
            if pivot < product.value {
                pivot = product.value
            }
        }
    }
    return pivot
}

func calculateDiagonalLeft(target [][]int, length int, size int, product *Product, pivot int) int {
    for i := size - 1; i < length; i++ {
        product.value = 1
        product.indexRow = 0
        product.indexColumn = i
        pivot = calculateLeft(target, length, size, product, pivot)
    }

    for i := length - size; i > 0; i-- {
        product.value = 1
        product.indexRow = i
        product.indexColumn = length - 1
        pivot = calculateLeft(target, length, size, product, pivot)
    }
    return pivot
}

func calculateDiagonalRight(target [][]int, length int, size int, product *Product, pivot int) int {
    for i := length - size; i >= 0; i-- {
        product.value = 1
        product.indexRow = 0
        product.indexColumn = i
        pivot = calculateRight(target, length, size, product, pivot)
    }

    for i := length - size; i > 0; i-- {
        product.value = 1
        product.indexRow = i
        product.indexColumn = 0
        pivot = calculateRight(target, length, size, product, pivot)
    }
    return pivot
}

func calculateLeft(target [][]int, length int, size int, product *Product, pivot int) int {
    multiplyLeft(target, length, size, product)
    if pivot < product.value {
        pivot = product.value
    }

    for product.indexRow < length && product.indexColumn >= 0 {
        value := target[product.indexRow][product.indexColumn]
        if 0 != value {
            product.value = product.value / target[product.indexRow - size][product.indexColumn + size] * value
            product.indexRow++
            product.indexColumn--
        } else {
            product.value = 1
            product.indexRow++
            product.indexColumn--
            multiplyLeft(target, length, size, product)
        }
        if pivot < product.value {
            pivot = product.value
        }
    }
    return pivot
}

func calculateRight(target [][]int, length int, size int, product *Product, pivot int) int {
    multiplyRight(target, length, size, product)
    if pivot < product.value {
        pivot = product.value
    }

    for product.indexRow < length && product.indexColumn < length {
        value := target[product.indexRow][product.indexColumn]
        if 0 != value {
            product.value = product.value / target[product.indexRow - size][product.indexColumn - size] * value
            product.indexRow++
            product.indexColumn++
        } else {
            product.value = 1
            product.indexRow++
            product.indexColumn++
            multiplyRight(target, length, size, product)
        }
        if pivot < product.value {
            pivot = product.value
        }
    }
    return pivot
}

func multiplyRow(target [][]int, length int, size int, product *Product) {
    if product.indexColumn + size > length {
        product.value = 1
        product.indexColumn = length
        return
    }

    for i := 0; i < size; i++ {
        value := target[product.indexRow][product.indexColumn]
        if 0 == value {
            product.value = 1
            product.indexColumn++
            multiplyRow(target, length, size, product)
            return
        }

        product.value *= value
        product.indexColumn++
    }
}

func multiplyColumn(target [][]int, length int, size int, product *Product) {
    if product.indexRow + size > length {
        product.value = 1
        product.indexRow = length
        return
    }

    for i := 0; i < size; i++ {
        value := target[product.indexRow][product.indexColumn]
        if 0 == value {
            product.value = 1
            product.indexRow++
            multiplyColumn(target, length, size, product)
            return
        }

        product.value *= value
        product.indexRow++
    }
}

func multiplyLeft(target [][]int, length int, size int, product *Product) {
    if product.indexRow + size > length || product.indexColumn - size + 1 < 0 {
        product.value = 1
        product.indexRow = length
        product.indexColumn = -1
        return
    }

    for i := 0; i < size; i++ {
        value := target[product.indexRow][product.indexColumn]
        if 0 == value {
            product.value = 1
            product.indexRow++
            product.indexColumn--
            multiplyLeft(target, length, size, product)
            return
        }

        product.value *= value
        product.indexRow++
        product.indexColumn--
    }
}

func multiplyRight(target [][]int, length int, size int, product *Product) {
    if product.indexRow + size > length || product.indexColumn + size > length {
        product.value = 1
        product.indexRow = length
        product.indexColumn = length
        return
    }

    for i := 0; i < size; i++ {
        value := target[product.indexRow][product.indexColumn]
        if 0 == value {
            product.value = 1
            product.indexRow++
            product.indexColumn++
            multiplyRight(target, length, size, product)
            return
        }

        product.value *= value
        product.indexRow++
        product.indexColumn++
    }
}

type Product struct {
    value int
    indexRow int
    indexColumn int
}
