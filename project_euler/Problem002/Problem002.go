package project_euler

import "fmt"

func Problem002() {
    target := 4000000
    previous := [2]int{2, 8}
    result := previous[0] + previous[1]
    for true {
        current := previous[0] + (previous[1] << 2)
        if current > target {
            break
        }

        result += current
        previous[0] = previous[1]
        previous[1] = current
    }
    fmt.Println(result)
}
