package project_euler

import "fmt"

func Problem052() {
    target := 6
    pivots := make([]int, 10)
    digits := make([]int, 10)
    index := 10
    for true {
        getDigits(index, pivots)
        isSame := true
        for i := target; i > 1; i-- {
            getDigits(index * i, digits)
            if !checkDigits(pivots, digits) {
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

func checkDigits(pivots []int, digits []int) bool {
    for i := 0; i < 10; i++ {
        if pivots[i] != digits[i] {
            return false
        }
    }
    return true
}
