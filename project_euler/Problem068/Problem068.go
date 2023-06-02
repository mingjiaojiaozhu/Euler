package project_euler

import "fmt"

func Problem068() {
    target := 10
    border := target >> 1
    start := border + 1
    summation := ((target * (target + 1) >> 1) + (border * (border + 1) >> 1)) / border
    pivot := summation - border - start

    ring := make([]int, 0)
    ring = append(ring, start)
    ring = append(ring, border)
    ring = append(ring, pivot)
    for i := target; i > start; i-- {
        ring = append(ring, i)
        ring = append(ring, pivot)
        pivot = summation - pivot - i
        ring = append(ring, pivot)
    }

    result := int64(0)
    for _, value := range ring {
        if value >= 10 {
            result = result * 100 + int64(value)
        } else {
            result = result * 10 + int64(value)
        }
    }
    fmt.Println(result)
}
