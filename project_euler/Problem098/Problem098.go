package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "math"
    "os"
    "strings"
)

func Problem098() {
    fileName := "words.txt"
    wordPairs := make([][]string, 0)
    length := getWordPair(fileName, &wordPairs)

    squares := make([]map[int64]bool, length - 2)
    for i := length - 3; i >= 0; i-- {
        squares[i] = make(map[int64]bool)
    }
    getSquares(squares, length)

    result := int64(0)
    letters := make([]int, 26)
    digits := make([]byte, 10)
    for _, words := range wordPairs {
        size := len(words[0])
        auxiliary := squares[size - 3]
        for pivot := range auxiliary {
            if setDigits(words[0], pivot, letters, digits, size) {
                value := getDigits(words[1], letters)
                if auxiliary[value] && (result < value || result < pivot) {
                    result = int64(math.Max(float64(value), float64(pivot)))
                }
            }
        }
    }
    fmt.Println(result)
}

func getWordPair(fileName string, wordPairs *[][]string) int {
    auxiliary := make([]string, 0)
    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        elements := strings.Replace(string(line), "\n", "", -1)
        if len(elements) > 2 {
            auxiliary = append(auxiliary, elements)
        }
    }
    file.Close()

    letters := make([][]int, 2)
    for i := 0; i < 2; i++ {
        letters[i] = make([]int, 26)
    }
    result := 0
    for i, pivot := range auxiliary {
        getLetters(pivot, letters[0])
        length := len(pivot)
        isPair := false
        for j := 0; j < i; j++ {
            word := auxiliary[j]
            if length == len(word) {
                getLetters(word, letters[1])
                if checkLetters(letters) {
                    *wordPairs = append(*wordPairs, []string{word, pivot})
                    isPair = true
                }
            }
        }
        if isPair && result < length {
            result = length
        }
    }
    return result
}

func getSquares(squares []map[int64]bool, length int) {
    border := int64(math.Pow(10, float64(length)))
    size := 2
    index := int64(10)
    for true {
        value := index * index
        if value >= border {
            break
        }

        if size != int(math.Log10(float64(value))) {
            size++
        }
        squares[size - 2][value] = true
        index++
    }
}

func setDigits(word string, value int64, letters []int, digits []byte, length int) bool {
    for i := 0; i < 26; i++ {
        letters[i] = -1
    }
    for i := 0; i < 10; i++ {
        digits[i] = ' '
    }

    for i := length - 1; i >= 0; i-- {
        letter := word[i]
        index := int(letter) - 'A'
        remainder := int(value % 10)
        if (-1 != letters[index] && remainder != letters[index]) || (' ' != digits[remainder] && index != int(digits[remainder])) {
            return false
        }
        letters[index] = remainder
        digits[remainder] = letter
        value /= 10
    }
    return true
}

func getDigits(word string, letters []int) int64 {
    result := int64(0)
    for _, letter := range word {
        result = result * 10 + int64(letters[int(letter) - 'A'])
    }
    return result
}

func getLetters(word string, letters []int) {
    for i := 0; i < 26; i++ {
        letters[i] = 0
    }
    for _, letter := range word {
        letters[int(letter) - 'A']++
    }
}

func checkLetters(letters [][]int) bool {
    for i := 0; i < 26; i++ {
        if letters[0][i] != letters[1][i] {
            return false
        }
    }
    return true
}
