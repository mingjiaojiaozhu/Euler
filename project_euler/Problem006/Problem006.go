package project_euler

import "fmt"

func Problem006() {
    target := 100
    result := target * (target - 1) * (target + 1) * (3 * target + 2) / 12
    fmt.Println(result)
}
