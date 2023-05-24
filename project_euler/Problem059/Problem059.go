package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "os"
    "strconv"
    "strings"
)

func Problem059() {
    fileName := "cipher.txt"
    codes := make([]int, 0)
    counts := make([]map[int]int, 3)
    for i := 0; i < 3; i++ {
        counts[i] = make(map[int]int)
    }

    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    index := 0
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        code, _ := strconv.Atoi(strings.Replace(string(line), "\n", "", -1))
        codes = append(codes, code)
        _, exist := counts[index][code]
        if exist {
            counts[index][code] += 1
        } else {
            counts[index][code] = 1
        }
        index++
        if 3 == index {
            index = 0
        }
    }
    file.Close()

    keys := make([]int, 3)
    for i := 0; i < 3; i++ {
        pivot := 0
        for key, value := range counts[i] {
            if pivot < value {
                pivot = value
                keys[i] = key
            }
        }
        keys[i] ^= int(' ')
    }

    result := 0
    index = 0
    for _, code := range codes {
        result += code ^ keys[index]
        index++
        if 3 == index {
            index = 0
        }
    }
    fmt.Println(result)
}
