package project_euler

import "fmt"

func Problem076() {
    target := 100
    ways := make([]int, target + 1)
    for i := 1; i <= target; i++ {
        ways[i] = 0
    }
    ways[0] = 1
    for i := 1; i < target; i++ {
        for j := i; j <= target; j++ {
            ways[j] += ways[j - i]
        }
    }
    fmt.Println(ways[target])
}
