package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "os"
    "strconv"
    "strings"
)

func Problem082() {
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

    ways := make([]int, border)
    for i := 0; i < border; i++ {
        ways[i] = target[i][border - 1]
    }
    for i := border - 2; i >= 0; i-- {
        ways[0] += target[0][i]
        for j := 1; j < border; j++ {
            if ways[j] > ways[j - 1] {
                ways[j] = ways[j - 1] + target[j][i]
            } else {
                ways[j] += target[j][i]
            }
        }
        for j := border - 2; j >= 0; j-- {
            if ways[j] > ways[j + 1] + target[j][i] {
                ways[j] = ways[j + 1] + target[j][i]
            }
        }
    }

    result := ways[0]
    for _, value := range ways {
        if result > value {
            result = value
        }
    }
    fmt.Println(result)
}
