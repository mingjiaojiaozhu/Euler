package project_euler

import (
    "fmt"
)

func Problem038() {
    digits := make([]bool, 9)
    for i := 9487; i >= 9234; i-- {
        for j := 0; j < 9; j++ {
            digits[j] = false
        }

        if (isPandigital(i, digits) && isPandigital(i << 1, digits)) {
            fmt.Printf("%d%d\n", i, i << 1)
            return
        }
    }
}

func isPandigital(value int, digits []bool) bool {
    for 0 != value {
        index := value % 10 - 1
        if index < 0 || digits[index] {
            return false
        }
        digits[index] = true
        value /= 10
    }
    return true
}
