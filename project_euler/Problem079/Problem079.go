package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "os"
    "strconv"
    "strings"
)

func Problem079() {
    fileName := "keylog.txt"
    length := 10
    elements := make([][]int, length)
    for i := 0; i < length; i++ {
        elements[i] = make([]int, length)
        for j := 0; j < length; j++ {
            elements[i][j] = 0
        }
    }
    visited := make([]bool, length)
    for i := 0; i < length; i++ {
        visited[i] = true
    }

    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        value, _ := strconv.Atoi(strings.Replace(string(line), "\n", "", -1))
        createElements(value, elements, visited)
    }
    file.Close()

    digits := make([]int, 0)
    for i := 0; i < length; i++ {
        if !visited[i] {
            search(elements, i, &digits, visited, length)
        }
    }

    result := 0
    for i := len(digits) - 1; i >= 0; i-- {
        result = result * 10 + digits[i]
    }
    fmt.Println(result)
}

func createElements(value int, elements [][]int, visited []bool) {
    tail := value % 10
    visited[tail] = false
    for value >= 10 {
        value /= 10
        head := value % 10
        elements[head][tail] = 1
        tail = head
        visited[tail] = false
    }
}

func search(elements [][]int, start int, digits *[]int, visited []bool, length int) {
    visited[start] = true
    element := elements[start]
    for i := 0; i < length; i++ {
        if 0 != element[i] && !visited[i] {
            search(elements, i, digits, visited, length)
        }
    }
    *digits = append(*digits, start)
}
