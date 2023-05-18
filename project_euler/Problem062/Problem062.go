package project_euler

import (
    "fmt"
    "math"
)

func Problem062() {
    target := 5
    cubes := make(map[int64][]int64)
    index := 5
    pivot := 0
    for true {
        value := int64(math.Pow(float64(index), 3))
        digits := getDigits(value)
        count := int(math.Log10(float64(value)))
        if pivot != count {
            cubes = make(map[int64][]int64)
            pivot = count
        } else {
            cube, exist := cubes[digits]
            if exist && len(cube) == target - 1 {
                fmt.Println(cube[0])
                return
            }
        }
        _, exist := cubes[digits]
        if !exist {
            cubes[digits] = make([]int64, 0)
        }
        cubes[digits] = append(cubes[digits], value)
        index++
    }
}

func getDigits(value int64) int64 {
    result := int64(0)
    for 0 != value {
        result += int64(math.Pow(10, float64(value % 10)))
        value /= 10
    }
    return result
}
