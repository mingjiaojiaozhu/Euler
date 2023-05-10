package project_euler

import (
    "fmt"
    "math"
    "sort"
)

func Problem029() {
    start := 2
    end := 100
    terms := make([]float64, 0)
    for i := start; i <= end; i++ {
        for j := start; j <= end; j++ {
            terms = append(terms, float64(i) * math.Log(float64(j)))
        }
    }

    sort.Float64s(terms)

    result := len(terms)
    for i := result - 1; i >= 1; i-- {
        if math.Abs(terms[i] - terms[i - 1]) < 0.00000001 {
            result--
        }
    }
    fmt.Println(result)
}
