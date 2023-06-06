package project_euler

import (
    "fmt"
    "math"
)

func Problem061() {
    target := 6
    polygonals := make([]Polygonal, 0)
    addTriangle(&polygonals)
    addSquare(&polygonals)
    addPentagonal(&polygonals)
    addHexagonal(&polygonals)
    addHeptagonal(&polygonals)
    addOctagonal(&polygonals)

    length := len(polygonals)
    edges := make([][]int, length)
    for i := 0; i < length; i++ {
        edges[i] = make([]int, length)
        for j := 0; j < length; j++ {
            edges[i][j] = 0
        }
    }
    for i := 0; i < length; i++ {
        pivot := polygonals[i]
        for j := i + 1; j < length; j++ {
            polygonal := polygonals[j]
            if pivot.step != polygonal.step {
                if pivot.tail == polygonal.head {
                    edges[i][j] = 1
                }
                if polygonal.tail == pivot.head {
                    edges[j][i] = 1
                }
            }
        }
    }

    indexes := make([]int, 0)
    steps := make([]bool, target)
    for i := 0; i < target; i++ {
        steps[i] = false
    }
    pivot := polygonals[0].step
    steps[pivot] = true
    for i := 0; i < length; i++ {
        indexes = append(indexes, i)
        step := polygonals[i].step
        if step != pivot {
            return
        }
        search(polygonals, edges, i, indexes, steps, target)
        indexes = indexes[:len(indexes) - 1]
    }
}

func addTriangle(polygonals *[]Polygonal) {
    start := int(math.Ceil((math.Sqrt(8001) - 1) / 2))
    end := int(math.Ceil((math.Sqrt(80001) - 1) / 2))
    for i := start; i < end; i++ {
        value := i * (i + 1) >> 1
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 0})
        }
    }
}

func addSquare(polygonals *[]Polygonal) {
    start := int(math.Ceil(math.Sqrt(1000)))
    end := int(math.Ceil(math.Sqrt(10000)))
    for i := start; i < end; i++ {
        value := i * i
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 1})
        }
    }
}

func addPentagonal(polygonals *[]Polygonal) {
    start := int(math.Ceil((math.Sqrt(24001) + 1) / 6))
    end := int(math.Ceil((math.Sqrt(240001) + 1) / 6))
    for i := start; i < end; i++ {
        value := i * (3 * i - 1) >> 1
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 2})
        }
    }
}

func addHexagonal(polygonals *[]Polygonal) {
    start := int(math.Ceil((math.Sqrt(8001) + 1) / 4))
    end := int(math.Ceil((math.Sqrt(80001) + 1) / 4))
    for i := start; i < end; i++ {
        value := i * ((i << 1) - 1)
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 3})
        }
    }
}

func addHeptagonal(polygonals *[]Polygonal) {
    start := int(math.Ceil((math.Sqrt(40009) + 3) / 10))
    end := int(math.Ceil((math.Sqrt(400009) + 3) / 10))
    for i := start; i < end; i++ {
        value := i * (5 * i - 3) >> 1
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 4})
        }
    }
}

func addOctagonal(polygonals *[]Polygonal) {
    start := int(math.Ceil((math.Sqrt(12002) + 2) / 6))
    end := int(math.Ceil((math.Sqrt(120002) + 2) / 6))
    for i := start; i < end; i++ {
        value := i * (3 * i - 2)
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 5})
        }
    }
}

func search(polygonals []Polygonal, edges [][]int, start int, indexes []int, steps []bool, target int) {
    if len(indexes) == target {
        if polygonals[indexes[0]].head == polygonals[indexes[target - 1]].tail {
            result := 0
            for _, index := range indexes {
                vertex := polygonals[index]
                result += vertex.head * 100 + vertex.tail
            }
            fmt.Println(result)
        }
        return
    }

    for i := len(polygonals) - 1; i >= 0; i-- {
        if 0 != edges[start][i] {
            step := polygonals[i].step
            if !steps[step] {
                indexes = append(indexes, i)
                steps[step] = true
                search(polygonals, edges, i, indexes, steps, target)
                indexes = indexes[:len(indexes) - 1]
                steps[step] = false
            }
        }
    }
}

type Polygonal struct {
    head int
    tail int
    step int
}
