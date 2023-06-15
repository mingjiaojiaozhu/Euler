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

func Problem081() {
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

    for i := 1; i < border; i++ {
        target[0][i] += target[0][i - 1]
        target[i][0] += target[i - 1][0]
    }
    for i := 1; i < border; i++ {
        for j := 1; j < border; j++ {
            target[i][j] += int(math.Min(float64(target[i-1][j]), float64(target[i][j-1])))
        }
    }
    fmt.Println(target[border - 1][border - 1])
}
