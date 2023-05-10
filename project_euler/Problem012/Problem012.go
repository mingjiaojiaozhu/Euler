package project_euler

import "fmt"

func Problem012() {
    target := 500
    previous := getDivisors(1)
    index := 1
    for true {
        current := getDivisors(index + 1)
        value := previous * current
        if value > target {
            break
        }

        index++
        previous = current
    }
    result := index * (index + 1) >> 1
    fmt.Println(result)
}

func getDivisors(value int) int {
    result := 1
    if 0 == (value & 1) {
        power := 0
        for 0 == (value & 1) {
            value >>= 1
            power++
        }
        result *= power
    }

    factor := 3
    for factor <= value {
        power := 0
        for 0 == value % factor {
            value /= factor
            power++
        }
        result *= power + 1
        factor += 2
    }
    return result
}
