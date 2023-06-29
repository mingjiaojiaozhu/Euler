package project_euler

import (
    "fmt"
    "math"
)

func Problem095() {
    target := 1000000
    divisors := make([]int64, target)
    for i := 0; i < target; i++ {
        divisors[i] = int64(-1)
    }
    for i := 2; i <= target; i++ {
        getDivisorSummation(i, divisors, target)
    }
    for i := 1; i < target; i++ {
        divisors[i] -= int64(i + 1)
    }

    result := 0
    pivot := 0
    chains := make(map[int]bool)
    for i := 2; i <= target; i++ {
        count := getChain(int64(i), divisors, &chains, target)
        if pivot < count {
            pivot = count
            result = target
            for key := range chains {
                if result > key {
                    result = key
                }
            }
        }

    }
    fmt.Println(result)
}

func getDivisorSummation(value int, divisors []int64, length int) {
    if -1 == divisors[value - 1] {
        index := int64(value)
        count := 1
        for index <= int64(length) {
            divisors[int(index) - 1] = (int64(math.Pow(float64(value), float64(count + 1))) - 1) / int64(value - 1)
            index *= int64(value)
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

func getChain(value int64, divisors []int64, chains *map[int]bool, target int) int {
    *chains = make(map[int]bool)
    (*chains)[int(value)] = true

    pivot := value
    count := 0
    for true {
        value = divisors[int(value) - 1]
        if pivot == value {
            break
        }
        if 1 == value || value >= int64(target) || (*chains)[int(value)] {
            return 0
        }

        (*chains)[int(value)] = true
        count++
    }
    return count
}

func isRelativelyPrime(i int, j int) bool {
    for 0 != i % j {
        i, j = j, i % j
    }
    return 1 == j
}
