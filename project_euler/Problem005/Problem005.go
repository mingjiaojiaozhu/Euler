package project_euler

import "fmt"

func Problem005() {
    target := 20
    powers := make([]int, target)
    for i := 0; i < target; i++ {
        powers[i] = 0
    }
    for i := 2; i <= target; i++ {
        factorize(i, powers)
    }

    result := int64(1)
    for i, power := range powers {
        for j := 0; j < power; j++ {
            result *= int64(i + 1)
        }
    }
    fmt.Println(result)
}

func factorize(value int, powers []int) {
    power := 0
    for 0 == (value & 1) {
        value >>= 1
        power++
    }
    if powers[1] < power {
        powers[1] = power
    }

    factor := 3
    for factor <= value {
        power = 0
        for 0 == value % factor {
            value /= factor
            power++
        }
        if powers[factor - 1] < power {
            powers[factor - 1] = power
        }
        factor += 2
    }
}
