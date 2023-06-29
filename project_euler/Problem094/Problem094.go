package project_euler

import (
    "fmt"
    "math"
)

func Problem094() {
    target := 1000000000
    index := []int{2, 1}
    result := int64(0)
    for true {
        index[0], index[1] = (index[0] << 1) + index[1] * 3, index[0] + (index[1] << 1)
        value := getTriangle(index, -1, target)
        if -1 == value {
            break
        }
        result += int64(value)

        value = getTriangle(index, 1, target)
        if -1 == value {
            break
        }
        result += int64(value)
    }
    fmt.Println(result)
}

func getTriangle(index []int, offset int, target int) int {
    perimeter := (index[0] + offset) << 1
    if perimeter >= target {
        return -1
    }

    length := float64((index[0] << 1) + offset) / 3
    if math.Abs(math.Floor(length + 0.5) - length) > 0.00000001 {
        return 0
    }
    area := (length + float64(offset)) * float64(index[1]) / 2
    if math.Abs(math.Floor(area + 0.5) - area) > 0.00000001 {
        return 0
    }
    return perimeter
}
