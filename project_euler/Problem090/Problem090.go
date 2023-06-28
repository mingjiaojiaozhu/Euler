package project_euler

import "fmt"

func Problem090() {
    elements := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 6}
    ways := make([][]int, 0)
    auxiliary := make([]int, 6)
    combination(elements, 0, 6, &ways, auxiliary, 0)

    squares := make([]int, 0)
    for i := 1; i < 10; i++ {
        squares = append(squares, reverse9To6(i * i))
    }

    result := 0
    arrangements := make(map[int]bool)
    for i := range ways {
        for j := 0; j <= i; j++ {
            if checkDigits(ways, i, j, squares, arrangements) {
                result++
            }
        }
    }
    fmt.Println(result)
}

func combination(elements []int, index int, count int, ways *[][]int, auxiliary []int, size int) {
    if count == size {
        *ways = append(*ways, make([]int, count))
        copy((*ways)[len(*ways) - 1], auxiliary)
        return
    }

    for i, value := range elements[index:] {
        auxiliary[size] = value
        size++
        combination(elements, index + i + 1, count, ways, auxiliary, size)
        size--
    }
}

func reverse9To6(value int) int {
    if 9 == value / 10 {
        value -= 30
    }
    if 9 == value % 10 {
        value -= 3
    }
    return value
}

func checkDigits(ways [][]int, start int, end int, squares []int, arrangements map[int]bool) bool {
    arrangements = make(map[int]bool)
    for _, pivot := range ways[start] {
        for _, value := range ways[end] {
            arrangements[pivot * 10 + value] = true
            arrangements[value * 10 + pivot] = true
        }
    }

    for _, value := range squares {
        if !arrangements[value] {
            return false
        }
    }
    return true
}
