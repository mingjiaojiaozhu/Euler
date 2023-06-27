package project_euler

import "fmt"

func Problem052() {
    target := 6
    digits := make([][]int, 2)
    for i := 0; i < 2; i++ {
        digits[i] = make([]int, 10)
    }
    index := 10
    for true {
        getDigits(index, digits[0])
        isSame := true
        for i := target; i > 1; i-- {
            getDigits(index * i, digits[1])
            if !checkDigits(digits) {
                isSame = false
                break
            }
        }
        if isSame {
            fmt.Println(index)
            return
        }
        index++
    }
}

func getDigits(value int, digits []int) {
    for i := 0; i < 10; i++ {
        digits[i] = 0
    }

    for 0 != value {
        digits[value % 10]++
        value /= 10
    }
}

func checkDigits(digits [][]int) bool {
    for i := 0; i < 10; i++ {
        if digits[0][i] != digits[1][i] {
            return false
        }
    }
    return true
}
