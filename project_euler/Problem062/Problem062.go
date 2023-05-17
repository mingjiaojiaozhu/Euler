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
        summation := getSummation(value)
        digit := int(math.Log10(float64(value)))
        if pivot != digit {
            cubes = make(map[int64][]int64)
            pivot = digit
        } else {
            cube, exist := cubes[summation]
            if exist && len(cube) == target - 1 {
                fmt.Println(cube[0])
                return
            }
        }
        _, exist := cubes[summation]
        if !exist {
            cubes[summation] = make([]int64, 0)
        }
        cubes[summation] = append(cubes[summation], value)
        index++
    }
}

func getSummation(value int64) int64 {
    result := int64(0)
    for 0 != value {
        result += int64(math.Pow(10, float64(value % 10)))
        value /= 10
    }
    return result
}
