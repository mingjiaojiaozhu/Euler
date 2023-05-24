package project_euler

import (
    "fmt"
    "math"
)

func Problem041() {
    elements := []int{7, 6, 5, 4, 3, 2, 1}
    result := permutation(elements, 0, len(elements), int64(0))
    fmt.Println(result)
}

func permutation(elements []int, index int, length int, pivot int64) int64 {
    if index == length {
        result := int64(0)
        for _, element := range elements {
            result = result * 10 + int64(element)
        }
        if isPrime(result) {
            return int64(math.Max(float64(result), float64(pivot)))
        }
        return pivot
    }

    result := permutation(elements, index + 1, length, pivot)
    for i := index + 1; i < length; i++ {
        elements[index], elements[i] = elements[i], elements[index]
        result = permutation(elements, index + 1, length, result)
        elements[index], elements[i] = elements[i], elements[index]
    }
    return result
}

func isPrime(value int64) bool {
    if 1 != value % 6 && 5 != value % 6 {
        return 2 == value || 3 == value
    }

    border := int64(math.Sqrt(float64(value)))
    for i := int64(5); i <= border; i += 6 {
        if 0 == value % i || 0 == value % (i + 2) {
            return false
        }
    }
    return 1 != value
}
