package project_euler

import "fmt"

func Problem039() {
    target := 1000
    result := 0
    pivot := 0
    for i := target; i >= 2; i -= 2 {
        count := 0
        for j := i / 3; j > 0; j-- {
            if 0 == (((i * i) >> 1) - i * j) % (i - j) && j < (((i * i) >> 1) - i * j) / (i - j) {
                count++
            }
        }
        if pivot < count {
            pivot = count
            result = i
        }
    }
    fmt.Println(result)
}
