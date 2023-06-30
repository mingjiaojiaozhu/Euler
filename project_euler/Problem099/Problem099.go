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

func Problem099() {
    fileName := "base_exp.txt"
    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    index := 1
    pivot := float64(0)
    result := 0
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        elements := strings.Split(strings.Replace(string(line), "\n", "", -1), " ")
        auxiliary, _ := strconv.Atoi(elements[0])
        value := math.Log(float64(auxiliary))
        auxiliary, _ = strconv.Atoi(elements[1])
        value *= float64(auxiliary)
        if pivot < value {
            pivot = value
            result = index
        }
        index++
    }
    file.Close()
    fmt.Println(result)
}
