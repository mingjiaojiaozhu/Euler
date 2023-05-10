package project_euler

import "fmt"

func Problem019() {
    start := 1900
    end := 2000
    days := []int{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    length := len(days)

    week := 1
    for _, day := range days {
        week += day
    }
    if 0 == start % 4 && (0 != start % 100 || 0 == start % 400) {
        week++
    }
    week %= 7

    result := 0
    for i := start + 1; i <= end; i++ {
        for j := 0; j < length; j++ {
            if 0 == week {
                result++
            }

            week += days[j]
            if 1 == j && (0 == i % 4 && (0 != i % 100 || 0 == i % 400)) {
                week++
            }
            week %= 7
        }
    }
    fmt.Println(result)
}
