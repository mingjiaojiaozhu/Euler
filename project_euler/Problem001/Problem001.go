package project_euler

import "fmt"

func Problem001() {
    target := 1000
    result := getSummation(target, 3) + getSummation(target, 5) - getSummation(target, 3 * 5)
    fmt.Println(result)
}

func getSummation(border int, factor int) int {
    count := (border - 1) / factor
    return factor * count * (count + 1) >> 1
}
