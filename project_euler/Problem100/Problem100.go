package project_euler

import "fmt"

func Problem100() {
    target := int64(1000000000000)
    index := int64(1)
    result := int64(1)
    for index < target {
        result, index = (index << 1) + result * 3 - 2, index * 3 + (result << 2) - 3
    }
    fmt.Println(result)
}
