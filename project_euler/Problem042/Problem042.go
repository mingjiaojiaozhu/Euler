package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "math"
    "os"
)

func Problem042() {
    fileName := "words.txt"
    result := 0
    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        value := 0
        for _, letter := range line {
            value += int(letter) - 'A' + 1
        }
        auxiliary := math.Sqrt(float64((value << 3) + 1))
        if math.Abs(math.Floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && 0 != (int(auxiliary) & 1) {
            result++
        }
    }
    file.Close()
    fmt.Println(result)
}
