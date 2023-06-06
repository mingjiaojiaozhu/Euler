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
    delta := int(math.Sqrt(float64(target * 24 + 1)))
    borders := []int{(delta + 1) / 6 + 1, (delta - 1) / 6 + 1}
    factor := 1
    for i := 1; i < borders[1]; i++ {
        getSummation(&(*ways)[target - (i * (i * 3 - 1) >> 1)], factor, auxiliary)
        getSummation(&(*ways)[target - (i * (i * 3 + 1) >> 1)], factor, auxiliary)
        factor *= -1
    }
    if borders[0] != borders[1] {
        getSummation(&(*ways)[target - (borders[1] * (borders[1] * 3 - 1) >> 1)], factor, auxiliary)
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

func swapDecimal(previous *Decimal, current *Decimal) {
    length := int(math.Max(float64(previous.length), float64(current.length)))
    for i := 0; i < length; i++ {
        previous.value[i], current.value[i] = current.value[i], previous.value[i]
    }
    previous.length, current.length = current.length, previous.length
}

type Decimal struct {
    value []int
    length int
}
