package project_euler

import "fmt"

func Problem072() {
    target := 1000000
    fractions := make(map[int]int64)
    fractions[1] = getSummation(1)
    result := getFractions(target, fractions) - fractions[1]
    fmt.Println(result)
}

func getFractions(target int, fractions map[int]int64) int64 {
    value, exist := fractions[target]
    if exist {
        return value
    }

    index := 2
    result := int64(0)
    for index <= target {
        step := target / (target / index)
        result += int64(step - index + 1) * getFractions(target / step, fractions)
        index = step + 1
    }
    result = getSummation(target) - result
    fractions[target] = result
    return result
}

func getSummation(value int) int64 {
    return int64(value * (value + 1) >> 1)
}
