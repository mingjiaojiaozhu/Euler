package project_euler

import "fmt"

func Problem053() {
    target := 1000000
    result := 0
    for i := 23; i <= 100; i++ {
        result += i + 1 - (getIndex(i, target) << 1)
    }
    fmt.Println(result)
}

func getIndex(value int, target int) int {
    start := 0
    end := (value + 1) >> 1
    for start <= end {
        current := start + ((end - start) >> 1)
        if checkCombination(value, current, target) {
            start = current + 1
        } else {
            end = current - 1
        }
    }
    return start
}

func checkCombination(value int, count int, target int) bool {
    result := 1
    for i := 0; i < count; i++ {
        result = result * (value - i) / (i + 1)
        if result > target {
            return false
        }
    }
    return true
}
