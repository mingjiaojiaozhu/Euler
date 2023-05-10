package project_euler

import "fmt"

func Problem031() {
    target := 200
    coins := []int{1, 2, 5, 10, 20, 50, 100, 200}
    result := getWays(target, coins, len(coins)- 1)
    fmt.Println(result)
}

func getWays(target int, coins []int, index int) int {
    if 0 == target || 0 == index {
        return 1
    }

    if target < coins[index] {
        return getWays(target, coins, index - 1)
    }
    return getWays(target, coins, index - 1) + getWays(target - coins[index], coins, index)
}
