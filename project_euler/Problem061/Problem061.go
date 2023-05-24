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
    index := int(math.Ceil((math.Sqrt(8001) - 1) / 2))
    for true {
        value := index * (index + 1) >> 1
        if value >= 10000 {
            return
        }
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 0})
        }
        index++
    }
}

func addSquare(polygonals *[]Polygonal) {
    index := int(math.Ceil(math.Sqrt(1000)))
    for true {
        value := index * index
        if value >= 10000 {
            return
        }
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 1})
        }
        index++
    }
}

func addPentagonal(polygonals *[]Polygonal) {
    index := int(math.Ceil((math.Sqrt(24001) + 1) / 6))
    for true {
        value := index * (3 * index - 1) >> 1
        if value >= 10000 {
            return
        }
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 2})
        }
        index++
    }
}

func addHexagonal(polygonals *[]Polygonal) {
    index := int(math.Ceil((math.Sqrt(8001) + 1) / 4))
    for true {
        value := index * ((index << 1) - 1)
        if value >= 10000 {
            return
        }
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 3})
        }
        index++
    }
}

func addHeptagonal(polygonals *[]Polygonal) {
    index := int(math.Ceil((math.Sqrt(40009) + 3) / 10))
    for true {
        value := index * (5 * index - 3) >> 1
        if value >= 10000 {
            return
        }
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 4})
        }
        index++
    }
}

func addOctagonal(polygonals *[]Polygonal) {
    index := int(math.Ceil((math.Sqrt(12002) + 2) / 6))
    for true {
        value := index * (3 * index - 2)
        if value >= 10000 {
            return
        }
        if value % 100 >= 10 {
            *polygonals = append(*polygonals, Polygonal{value / 100, value % 100, 5})
        }
        index++
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
