package project_euler

import "fmt"

func Problem033() {
    numerator := 1
    denominator := 1
    for i := 1; i < 10; i++ {
        for j := i + 1; j < 10; j++ {
            if 0 == (9 * i * j) % (10 * i - j) && (9 * i * j) / (10 * i - j) < 10 {
                numerator *= i
                denominator *= j
            }
        }
    }
    fmt.Println(denominator / commonDivisor(denominator, numerator))
}

func commonDivisor(i int, j int) int {
    for 0 != i % j {
        i, j = j, i % j
    }
    return j
}
