package project_euler

import "fmt"

func Problem009() {
    target := 1000
    for i := target / 3; i > 0; i-- {
        for j := target >> 1; j > i; j-- {
            remainder := target - i - j
            if i * i + j * j == remainder * remainder {
                fmt.Println(i * j * remainder)
                return
            }
        }
    }
}
