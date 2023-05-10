package project_euler

import "fmt"

func Problem014() {
    target := 1000000
    chains := make([]int, target)
    for i := 2; i < target; i++ {
        chains[i] = -1
    }
    chains[0] = 1
    chains[1] = 2

    for i := 3; i <= target; i++ {
        getCollatz(int64(i), chains, target)
    }

    result := 0
    pivot := 0
    for i, chain := range chains[2:] {
        if pivot < chain {
            pivot = chain
            result = i + 3
        }
    }
    fmt.Println(result)
}

func getCollatz(value int64, chains []int, length int) int {
    if value <= int64(length) && -1 != chains[value - 1] {
        return chains[value - 1]
    }

    result := 0
    if 0 != (value & 1) {
        result = getCollatz(3 * value + 1, chains, length) + 1
    } else {
        result = getCollatz(value >> 1, chains, length) + 1
    }
    if value <= int64(length) {
        chains[value - 1] = result
    }
    return result
}
