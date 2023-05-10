package project_euler

import "fmt"

func Problem015() {
    target := 20
    border := target << 1
    result := int64(1)
    for i := border - 1; i > target; i -= 2 {
        result = (result << 1) * int64(i) / (int64(border - i + 1) >> 1)
    }
    fmt.Println(result)
}
