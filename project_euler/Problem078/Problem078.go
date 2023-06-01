package project_euler

import "fmt"

func Problem078() {
    target := 1000000
    ways := make([]Decimal, 0)
    ways = append(ways, setValue(1))
    ways = append(ways, setValue(1))

    length := 0
    for target >= int(1e5) {
        length++
        target /= int(1e5)
    }

    result := 2
    for true {
        way := getWay(result, &ways)
        if isDivideExactly(way, length, target) {
            fmt.Println(result)
            return
        }
        result++
    }
}

func setValue(value int) Decimal {
    decimal := Decimal{make([]int, 100), 0}
    for i := 1; i < 100; i++ {
        decimal.value[i] = 0
    }
    decimal.value[0] = value
    decimal.length = 1
    return decimal
}

func getWay(target int, ways *[]Decimal) Decimal {
    result := setValue(0)
    factor := 1
    for i := 1; i <= target; i++ {
        if !addDecimal(target - (i * (i * 3 - 1) >> 1), *ways, factor, &result) || !addDecimal(target - (i * (i * 3 + 1) >> 1), *ways, factor, &result) {
            break
        }
        factor *= -1
    }
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

func addDecimal(index int, ways []Decimal, factor int, result *Decimal) bool {
    if index < 0 {
        return false
    }
    getSummation(&ways[index], factor, result)
    return true
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
