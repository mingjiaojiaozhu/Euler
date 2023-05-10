package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "os"
    "sort"
    "strings"
)

func Problem022() {
    fileName := "names.txt"
    names := make([]string, 0)

    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        names = append(names, strings.Replace(string(line), "\n", "", -1))
    }
    file.Close()

    sort.Strings(names)

    result := int64(0)
    for i, name := range names {
        score := 0
        for _, letter := range name {
            score += int(letter) - 'A' + 1
        }
        result += int64(score * (i + 1))
    }
    fmt.Println(result)
}
