package project_euler

import "fmt"

func Problem004() {
    target := 100
    result := 0
    for i := 999; i >= target; i-- {
        for j := i; j >= target; j-- {
            value := i * j
            if isPalindrome(value) && result < value {
                result = value
                target = j
                break
            }
        }
    }
    fmt.Println(result)
}

func isPalindrome(value int) bool {
    divisor := 1
    for 10 <= value / divisor {
        divisor *= 10
    }

    for value > 1 {
        head := value / divisor
        tail := value % 10
        if head != tail {
            return false
        }

        value = value % divisor / 10
        divisor /= 100
    }
    return true
}
