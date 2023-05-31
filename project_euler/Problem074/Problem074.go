package project_euler

import (
    "fmt"
    "math"
)

func Problem074() {
    target := 60
    border := 1000000
    step := int(math.Log10(float64(border)))
    permutations := make([]int, 0)
    for i := 1; i < 10; i++ {
        permutations = append(permutations, i)
    }
    chains := make(map[int]bool)
    terms := make(map[int]int)
    factorials := make([]int, 10)
    factorials[0] = 1
    for i := 1; i < 10; i++ {
        factorials[i] = factorials[i - 1] * i
    }
    counts := make([]int, 10)
    auxiliary := make([]int, 0)
    result := 0
    for _, value := range permutations {
        if target == getTerms(value, chains, terms, factorials, counts) {
            result += getPermutations(value, factorials, counts)
        }
    }
    for i := 1; i < step; i++ {
        getDigits(&permutations, &auxiliary)
        for _, value := range permutations {
            if target == getTerms(value, chains, terms, factorials, counts) {
                result += getPermutations(value, factorials, counts)
            }
        }
    }
    fmt.Println(result)
}

func getTerms(value int, chains map[int]bool, terms map[int]int, factorials []int, counts []int) int {
    chains = make(map[int]bool)
    pivot := value
    result := 0
    for true {
        term, exist := terms[value]
        if exist {
            result = len(chains) + term
            break
        }
        if chains[value] {
            result = len(chains)
            break
        }

        chains[value] = true
        value = getSummation(value, factorials, counts)
    }
    terms[pivot] = result
    return result
}

func getPermutations(value int, factorials []int, counts []int) int {
    length := 0
    exists0 := false
    for i := 0; i < 10; i++ {
        counts[i] = 0
    }
    for 0 != value {
        length++
        remainder := value % 10
        if 0 == remainder {
            exists0 = true
        }
        counts[remainder]++
        value /= 10
    }

    result := factorials[length]
    if exists0 {
        result = result * (length - 1) / length
    }
    for _, count := range counts {
        if 1 != count {
            result /= factorials[count]
        }
    }
    return result
}

func getDigits(permutations *[]int, auxiliary *[]int) {
    for _, value := range *permutations {
        *auxiliary = append(*auxiliary, value)
    }
    *permutations = make([]int, 0)
    for _, value := range *auxiliary {
        remainder := value % 10
        for i := 0; i <= remainder; i++ {
            *permutations = append(*permutations, value * 10 + i)
        }
    }
    *auxiliary = make([]int, 0)
}

func getSummation(value int, factorials []int, counts []int) int {
    result := 0
    for 0 != value {
        result += factorials[value % 10]
        value /= 10
    }

    for i := 0; i < 10; i++ {
        counts[i] = 0
    }
    for 0 != result {
        counts[9 - result % 10]++
        result /= 10
    }

    for i, count := range counts {
        for j := 0; j < count; j++ {
            result = result * 10 + 9 - i
        }
    }
    return result
}
