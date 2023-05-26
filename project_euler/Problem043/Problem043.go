package project_euler

import "fmt"

func Problem043() {
    elements := make([]int, 10)
    elements[5] = 5
    digits := make([]bool, 10)
    for i := 0; i < 10; i++ {
        digits[i] = false
    }
    digits[5] = true

    start := 500
    for 0 != start % 11 {
        start++
    }

    result := int64(0)
    for i := start; i < 600; i += 11 {
        elements[6] = (i % 100) / 10
        elements[7] = i % 10
        if 5 != elements[6] && 5 != elements[7] && elements[6] != elements[7] {
            digits[elements[6]] = true
            digits[elements[7]] = true
            result += check13(elements, elements[6] * 100 + elements[7] * 10, digits)
            digits[elements[6]] = false
            digits[elements[7]] = false
        }
    }
    fmt.Println(result)
}

func check13(elements []int, pivot int, digits []bool) int64 {
    result := int64(0)
    for i := 0; i < 10; i++ {
        if !digits[i] && 0 == (pivot + i) % 13 {
            elements[8] = i
            digits[i] = true
            result += check17(elements, ((pivot + i) % 100) * 10, digits)
            digits[i] = false
        }
    }
    return result
}

func check17(elements []int, pivot int, digits []bool) int64 {
    result := int64(0)
    for i := 0; i < 10; i++ {
        if !digits[i] && 0 == (pivot + i) % 17 {
            elements[9] = i
            digits[i] = true
            fill(elements, digits)
            result += permutation(elements, 0, 5)
            digits[i] = false
        }
    }
    return result
}

func fill(elements []int, digits []bool) {
    index := 4
    for i := len(digits) - 1; i >= 0; i-- {
        if !digits[i] {
            elements[index] = i
            index--
        }
    }
}

func permutation(elements []int, index int, length int) int64 {
    if index == length {
        if 0 == elements[0] || 0 != (elements[3] & 1) || 0 != (elements[2] + elements[3] + elements[4]) % 3 || 0 != (10 * elements[4] + elements[5] - (elements[6] << 1)) % 7 {
            return int64(0)
        }

        result := int64(0)
        for _, element := range elements {
            result = result * 10 + int64(element)
        }
        return result
    }

    result := permutation(elements, index + 1, length)
    for i := index + 1; i < length; i++ {
        elements[index], elements[i] = elements[i], elements[index]
        result += permutation(elements, index + 1, length)
        elements[index], elements[i] = elements[i], elements[index]
    }
    return result
}
