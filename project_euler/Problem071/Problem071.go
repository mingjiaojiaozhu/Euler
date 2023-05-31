package project_euler

import "fmt"

func Problem071() {
    target := 1000000
    index := (target - 5) / 7
    result := index * 3 + 2
    fmt.Println(result)
}
