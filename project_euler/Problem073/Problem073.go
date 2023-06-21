package project_euler

import "fmt"

func Problem073() {
    target := 12000
    fractions := make(map[int]int)
    fractions[1] = getCount(1)
    result := getFractions(target, fractions) - fractions[1]
    fmt.Println(result)
}

func getFractions(target int, fractions map[int]int) int {
    value, exist := fractions[target]
    if exist {
        return value
    }

    index := 2
    result := 0
    for index <= target {
        step := target / (target / index)
        result += (step - index + 1) * getFractions(target / step, fractions)
        index = step + 1
    }
    result = getCount(target) - result
    fractions[target] = result
    return result
}

func getCount(value int) int {
    quotient := value / 6
    remainder := value % 6
    if 5 == remainder {
        return quotient * (quotient * 3 - 2 + remainder) + 1
    }
    return quotient * (quotient * 3 - 2 + remainder)
}
