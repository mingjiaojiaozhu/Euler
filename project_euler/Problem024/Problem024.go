package project_euler

import (
    "fmt"
)

func Problem024() {
    target := int64(1000000)
    elements := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    permutation(target - 1, elements, len(elements), 0)

    result := int64(0)
    for _, element := range elements {
        result = result * 10 + int64(element)
    }
    fmt.Println(result)
}

func permutation(sequence int64, elements []int, length int, start int) {
    if 1 == length - start {
        return
    }

    count := getFactorial(length - start - 1)
    index := int(sequence / count) + start
    if index != start {
        auxiliary := elements[index]
        for i := index; i > start; i-- {
            elements[i] = elements[i - 1]
        }
        elements[start] = auxiliary
    }
    start += 1
    permutation(sequence % count, elements, length, start)
}

func getFactorial(value int) int64 {
    result := int64(1)
    for i := 2; i <= value; i++ {
        result *= int64(i)
    }
    return result
}
