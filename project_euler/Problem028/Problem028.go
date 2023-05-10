package project_euler

import "fmt"

func Problem028() {
    target := 1001
    steps := target >> 1
    result := int64((steps * steps * steps * 16 + steps * 26) / 3 + steps * steps * 10 + 1)
    fmt.Println(result)
}
