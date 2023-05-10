package project_euler

import (
    "fmt"
    "math"
)

func Problem021() {
    target := 10000
    divisors := make([]int, target)
    for i := 0; i < target; i++ {
        divisors[i] = -1
    }
    for i := 2; i <= target; i++ {
        getDivisorSummation(i, divisors, target)
    }
    for i := 1; i < target; i++ {
        divisors[i] -= i + 1
    }

    result := 0
    for i := 2; i <= target; i++ {
        divisor := divisors[i - 1]
        if divisor > i && divisor <= target && divisors[divisor - 1] == i {
            result += i + divisor
        }

    }
    fmt.Println(result)
}

func getDivisorSummation(value int, divisors []int, length int) {
    if -1 == divisors[value - 1] {
        index := value
        count := 1
        for index <= length {
            divisors[index - 1] = (int(math.Pow(float64(value), float64(count + 1))) - 1) / (value - 1)
            index *= value
            count++
        }

        for i := int(math.Min(float64(value - 1), float64(length / value))); i >= 2; i-- {
            divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]
        }
    } else {
        for i := int(math.Min(float64(value - 1), float64(length / value))); i >= 2; i-- {
            if isRelativelyPrime(value, i) && -1 == divisors[value * i - 1] {
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]
            }
        }
    }
}

func isRelativelyPrime(i int, j int) bool {
    for 0 != i % j {
        i, j = j, i % j
    }
    return 1 == j
}
