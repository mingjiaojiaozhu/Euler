package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "math"
    "os"
    "strconv"
    "strings"
)

func Problem067() {
    fileName := "triangle.txt"
    border := 100
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

    for i := border - 1; i > 0; i-- {
        for j := i - 1; j >= 0; j-- {
            target[i - 1][j] += int(math.Max(float64(target[i][j]), float64(target[i][j + 1])))
        }
    }
    fmt.Println(target[0][0])
}
