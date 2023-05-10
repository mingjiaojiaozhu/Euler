package project_euler

import (
    "fmt"
    "math"
)

func Problem036() {
    target := 1000000
    border := int(math.Ceil(math.Sqrt(float64(target))))
    palindromes := make([]int, 2)
    binary := make([]bool, 0)

    result := 0
    for i := 1; i < border; i++ {
        getPalindrome(i, palindromes)
        if isBinaryPalindrome(palindromes[0], binary) {
            result += palindromes[0]
        }
        if isBinaryPalindrome(palindromes[1], binary) {
            result += palindromes[1]
        }
    }
    fmt.Println(result)
}

func getPalindrome(value int, palindromes []int) {
    palindromes[0] = value / 10
    palindromes[1] = value
    for 0 != value {
        palindromes[0] = palindromes[0] * 10 + value % 10
        palindromes[1] = palindromes[1] * 10 + value % 10
        value /= 10
    }
}

func isBinaryPalindrome(value int, binary []bool) bool {
    binary = make([]bool, 0)
    for 0 != value {
        binary = append(binary, 0 != (value & 1))
        value >>= 1
    }

    start := 0
    end := len(binary) - 1
    for start < end {
        if binary[start] != binary[end] {
            return false
        }
        start++
        end--
    }
    return true
}
