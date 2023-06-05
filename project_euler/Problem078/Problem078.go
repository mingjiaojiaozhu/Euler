package project_euler

import (
    "fmt"
    "math"
)

func Problem078() {
    target := 1000000
    ways := make([]Decimal, 0)
    ways = append(ways, setValue(1, 1))
    ways = append(ways, setValue(1, 1))

    length := 0
    for target >= int(1e5) {
        length++
        target /= int(1e5)
    }

    auxiliary := Decimal{make([]int, 100), 0}
    for i := 1; i < 100; i++ {
        auxiliary.value[i] = 0
    }
    result := 2
    for true {
        way := getWay(result, &ways, &auxiliary)
        if isDivideExactly(way, length, target) {
            fmt.Println(result)
            return
        }
        result++
    }
}

func setValue(value int, length int) Decimal {
    decimal := Decimal{make([]int, length), 0}
    for i := 1; i < length; i++ {
        decimal.value[i] = 0
    }
    decimal.value[0] = value
    decimal.length = 1
    return decimal
}

func getWay(target int, ways *[]Decimal, auxiliary *Decimal) Decimal {
    factor := 1
    for i := 1; i <= target; i++ {
        if !addDecimal(target - (i * (i * 3 - 1) >> 1), *ways, factor, auxiliary) || !addDecimal(target - (i * (i * 3 + 1) >> 1), *ways, factor, auxiliary) {
            break
        }
        factor *= -1
    }
    result := Decimal{make([]int, auxiliary.length), 0}
    for i := 1; i < auxiliary.length; i++ {
        result.value[i] = 0
    }
    swapDecimal(auxiliary, &result)
    *ways = append(*ways, result)
    return result
}

func isDivideExactly(way Decimal, length int, target int) bool {
    if way.length <= length {
        return false
    }

    for i := 0; i < length; i++ {
        if 0 != way.value[i] {
            return false
        }
    }
    return 0 == way.value[length] % target
}

func addDecimal(index int, ways []Decimal, factor int, summation *Decimal) bool {
    if index < 0 {
        return false
    }
    getSummation(&ways[index], factor, summation)
    return true
}

func swapDecimal(previous *Decimal, current *Decimal) {
    length := int(math.Max(float64(previous.length), float64(current.length)))
    for i := 0; i < length; i++ {
        previous.value[i], current.value[i] = current.value[i], previous.value[i]
    }
    previous.length, current.length = current.length, previous.length
}

func getSummation(decimal *Decimal, factor int, summation *Decimal) {
    for i := 0; i < decimal.length; i++ {
        summation.value[i] += decimal.value[i] * factor
    }

    if factor > 0 {
        for i := 0; i < summation.length; i++ {
            if summation.value[i] >= int(1e5) {
                summation.value[i+1] += summation.value[i] / int(1e5)
                summation.value[i] %= int(1e5)
            }
        }
        if 0 != summation.value[summation.length] {
            summation.length++
        }
    } else {
        for i := 0; i < summation.length; i++ {
            if summation.value[i] < 0 {
                summation.value[i + 1]--
                summation.value[i] += int(1e5)
            }
        }
        for 0 == summation.value[summation.length - 1] {
            summation.length--
        }
    }
}

type Decimal struct {
    value []int
    length int
}
