package project_euler

import "fmt"

func Problem017() {
    lettersBelow10 := []int{3, 3, 5, 4, 4, 3, 5, 5, 4}
    letters10To19 := []int{3, 6, 6, 8, 8, 7, 7, 9, 8, 8}
    lettersWholeTen := []int{6, 6, 5, 5, 5, 7, 6, 6}
    letter100 := 7
    letterAnd := 3
    letter1000 := 8

    countBelow10 := 0
    for _, letter := range lettersBelow10 {
        countBelow10 += letter
    }

    countBelow100 := countBelow10 * 9
    for _, letter := range letters10To19 {
        countBelow100 += letter
    }
    for _, letter := range lettersWholeTen {
        countBelow100 += letter * 10
    }

    result := countBelow100 * 10 + countBelow10 * 100 + letter100 * 100 * 9 + letterAnd * 99 * 9 + lettersBelow10[0] + letter1000
    fmt.Println(result)
}
