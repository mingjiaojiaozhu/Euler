package project_euler

import (
    "fmt"
    "math"
)

func Problem075() {
    target := 1500000
    border := int(math.Sqrt(float64(target >> 1)))
    perimeters := make(map[int]int)
    for i := 2; i <= border; i++ {
        for j := 1; j < i; j++ {
            if 0 != ((i + j) & 1) && isRelativelyPrime(i, j) {
                pivot := i * (i + j) << 1
                length := pivot
                for length < target {
                    _, exist := perimeters[length]
                    if exist {
                        perimeters[length] += 1
                    } else {
                        perimeters[length] = 1
                    }
                    length += pivot
                }
            }
        }
    }

    result := 0
    for _, value := range perimeters {
        if 1 == value {
            result++
        }
    }
    fmt.Println(result)
}

func isRelativelyPrime(i int, j int) bool {
    for 0 != i % j {
        i, j = j, i % j
    }
    return 1 == j
}
