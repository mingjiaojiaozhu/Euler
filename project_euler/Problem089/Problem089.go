package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "os"
    "strings"
)

func Problem089() {
    fileName := "roman.txt"
    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    result := 0
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        previous := ' '
        pivot := ' '
        count := 1
        for _, value := range strings.Replace(string(line), "\n", "", -1) {
            if pivot == value {
                count++
            } else {
                previous = pivot
                pivot = value
                count = 1
            }

            if count >= 4 {
                if ('I' == pivot && 'V' == previous) || ('X' == pivot && 'L' == previous) || ('C' == pivot && 'D' == previous) {
                    result += 3
                } else if 'M' != pivot {
                    result += 2
                }
            }
        }
    }
    file.Close()
    fmt.Println(result)
}
