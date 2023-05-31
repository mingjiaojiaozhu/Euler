package project_euler

import "fmt"

func Problem031() {
    target := 200
    coins := []int{1, 2, 5, 10, 20, 50, 100, 200}
    ways := make([]int, target + 1)
    for i := 1; i <= target; i++ {
        ways[i] = 0
    }
    ways[0] = 1
    for _, coin := range coins {
        for i := coin; i <= target; i++ {
            ways[i] += ways[i - coin]
        }
    }
    fmt.Println(ways[target])
}
