package project_euler

import (
    "fmt"
    "math"
)

func Problem060() {
    target := 5
    primes := make([]int, 0)
    for i := 3; i < 10000; i += 2 {
        if isPrime(i) {
            primes = append(primes, i)
        }
    }

    length := len(primes)
    edges := make([][]int, length)
    for i := 0; i < length; i++ {
        edges[i] = make([]int, length)
        for j := 0; j < length; j++ {
            edges[i][j] = 0
        }
    }
    for i := 1; i < length; i++ {
        value := primes[i]
        if checkPrime(merge(3, value), primes) && checkPrime(merge(value, 3), primes) {
            edges[0][i] = 1
            edges[i][0] = 1
        }
    }
    for i := 1; i < length; i++ {
        pivot := primes[i]
        for j := i + 1; j < length; j++ {
            value := primes[j]
            if pivot % 3 == value % 3 && checkPrime(merge(pivot, value), primes) && checkPrime(merge(value, pivot), primes) {
                edges[i][j] = 1
                edges[j][i] = 1
            }
        }
    }

    cliques := make([]int, 0)
    indexes := make([]int, 0)
    for i := 0; i < length; i++ {
        indexes = append(indexes, i)
    }
    search(primes, edges, cliques, indexes, target)
}

func isPrime(value int) bool {
    if 1 != value % 6 && 5 != value % 6 {
        return 2 == value || 3 == value
    }

    border := int(math.Sqrt(float64(value)))
    for i := 5; i <= border; i += 6 {
        if 0 == value % i || 0 == value % (i + 2) {
            return false
        }
    }
    return 1 != value
}

func checkPrime(value int, primes []int) bool {
    if value < 10000 {
        start := 0
        end := len(primes) - 1
        for start <= end {
            current := start + ((end - start) >> 1)
            prime := primes[current]
            if prime == value {
                return true
            }

            if prime < value {
                start = current + 1
            } else {
                end = current - 1
            }
        }
        return false
    }

    border := int(math.Sqrt(float64(value)))
    start := 0
    end := len(primes) - 1
    for start <= end {
        current := start + ((end - start) >> 1)
        if primes[current] <= border {
            start = current + 1
        } else {
            end = current - 1
        }
    }

    for _, prime := range primes[:start] {
        if 0 == value % prime {
            return false
        }
    }
    return true
}

func merge(head int, tail int) int {
    return head * int(math.Pow(10, float64(int(math.Log10(float64(tail))) + 1))) + tail
}

func search(primes []int, edges [][]int, cliques []int, indexes []int, target int) {
    if 0 == len(indexes) {
        if len(cliques) == target {
            result := 0
            for _, index := range cliques {
                result += primes[index]
            }
            fmt.Println(result)
        }
        return
    }

    start := indexes[0]
    for i := len(indexes) - 1; i >= 0; i-- {
        index := indexes[i]
        if 0 == edges[start][index] {
            cliques = append(cliques, index)
            search(primes, edges, cliques, getAdjacents(edges, indexes, index), target)
            cliques = cliques[:len(cliques) - 1]
            indexes = clear(indexes, index)
        }
    }
}

func getAdjacents(edges [][]int, indexes []int, start int) []int {
    auxiliary := make([]int, 0)
    for _, index := range indexes {
        if 0 != edges[start][index] {
            auxiliary = append(auxiliary, index)
        }
    }
    return auxiliary
}

func clear(arrays []int, value int) []int {
    for i := len(arrays) - 1; i >= 0; i-- {
        if arrays[i] == value {
            return append(arrays[:i], arrays[i + 1:]...)
        }
    }
    return arrays
}
