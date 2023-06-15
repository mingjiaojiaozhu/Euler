package project_euler

import (
    "bufio"
    "container/heap"
    "fmt"
    "io"
    "os"
    "strconv"
    "strings"
)

func Problem083() {
    fileName := "matrix.txt"
    border := 80
    target := make([][]int, border)
    for i := 0; i < border; i++ {
        target[i] = make([]int, border)
    }

    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    index := 0
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        elements := strings.Split(strings.Replace(string(line), "\n", "", -1), " ")
        for i, element := range elements {
            auxiliary, _ := strconv.Atoi(element)
            target[index][i] = auxiliary
        }
        index++
    }
    file.Close()

    length := border * border
    edges := make([][]int, length)
    for i := 0; i < length; i++ {
        edges[i] = make([]int, length)
        for j := 0; j < length; j++ {
            edges[i][j] = 0
        }
    }
    for i := 0; i < border; i++ {
        for j := 0; j < border; j++ {
            if i > 0 {
                edges[i * border + j][(i - 1) * border + j] = target[i - 1][j]
            }
            if j > 0 {
                edges[i * border + j][i * border + j - 1] = target[i][j - 1]
            }
            if i < border - 1 {
                edges[i * border + j][(i + 1) * border + j] = target[i + 1][j]
            }
            if j < border - 1 {
                edges[i * border + j][i * border + j + 1] = target[i][j + 1]
            }
        }
    }

    ways := make([]int, length)
    search(edges, length, ways)
    fmt.Println(ways[length - 1] + target[0][0])
}

func search(edges [][]int, length int, ways []int) {
    visited := make([]bool, length)
    for i := 0; i < length; i++ {
        visited[i] = false
    }
    queue := make(PriorityQueue, 0)
    heap.Push(&queue, Heap{0, 0})
    for len(queue) > 0 {
        node := heap.Pop(&queue).(Heap)
        index := node.index
        weight := node.weight
        if visited[index] {
            continue
        }

        ways[index] = weight
        visited[index] = true
        for i := 0; i < length; i++ {
            if 0 != edges[index][i] && !visited[i] {
                heap.Push(&queue, Heap{i, weight + edges[index][i]})
            }
        }
    }
}

func (queue PriorityQueue) Len() int {
    return len(queue)
}

func (queue PriorityQueue) Less(i int, j int) bool {
    return queue[i].weight < queue[j].weight
}

func (queue PriorityQueue) Swap(i int, j int) {
    queue[i], queue[j] = queue[j], queue[i]
}

func (queue *PriorityQueue) Push(node interface{}) {
    *queue = append(*queue, node.(Heap))
}

func (queue *PriorityQueue) Pop() interface{} {
    length := len(*queue)
    node := (*queue)[length - 1]
    *queue = (*queue)[:length - 1]
    return node
}

type Heap struct {
    index int
    weight int
}

type PriorityQueue []Heap
