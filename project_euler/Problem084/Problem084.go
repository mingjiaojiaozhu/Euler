package project_euler

import (
    "fmt"
    "math"
)

func Problem084() {
    target := 4
    length := 40
    dice := make([][]float64, length)
    for i := 0; i < length; i++ {
        dice[i] = make([]float64, length)
        for j := 0; j < length; j++ {
            dice[i][j] = 0
        }
    }
    setDice(dice, length, target)

    card := make([][]float64, length)
    for i := 0; i < length; i++ {
        card[i] = make([]float64, length)
        for j := 0; j < length; j++ {
            card[i][j] = 0
        }
    }
    setCard(card, length)

    probability := make([]float64, length)
    setProbability(probability, dice, card, length)

    size := 3
    squares := make([]Square, size)
    setSquares(squares, probability, size)

    result := 0
    if squares[1].value > squares[2].value {
        result = squares[1].index * 100 + squares[2].index
    } else {
        result = squares[2].index * 100 + squares[1].index
    }
    result = result * 100 + squares[0].index
    fmt.Println(result)
}

func setDice(dice [][]float64, length int, target int) {
    border := (target << 1) - 1
    chances := make([]float64, border)

    start := 0
    end := border - 1
    count := 1
    total := target * target
    for start < end {
        chance := float64(count) / float64(total)
        chances[start] = chance
        chances[end] = chance
        count++
        start++
        end--
    }
    chances[start] = float64(count) / float64(total)

    for i := length - border - 2; i >= 0; i-- {
        for j := 0; j < border; j++ {
            dice[i][i + j + 2] = chances[j]
        }
    }
    for i := length - border - 1; i < length - 2; i++ {
        for j := length - i - 3; j >= 0; j-- {
            dice[i][i + j + 2] = chances[j]
        }
        for j := length - i - 2; j < border; j++ {
            dice[i][i + j - length + 2] = chances[j]
        }
    }
    for i := length - 2; i < length; i++ {
        for j := 0; j < border; j++ {
            dice[i][i + j - length + 2] = chances[j]
        }
    }
}

func setCard(card [][]float64, length int) {
    for i := 0; i < length; i++ {
        card[i][i] = 1
    }
    setJail(card, 30)
    setCommunityChest(card, 2)
    setCommunityChest(card, 17)
    setCommunityChest(card, 33)
    setChance(card, 7)
    setChance(card, 22)
    setChance(card, 36)
}

func setProbability(probability []float64, dice [][]float64, card [][]float64, length int) {
    board := make([][]float64, length)
    for i := 0; i < length; i++ {
        board[i] = make([]float64, length)
        for j := 0; j < length; j++ {
            board[i][j] = 0
        }
    }
    for i := 0; i < length; i++ {
        for j := 0; j < length; j++ {
            for k := 0; k < length; k++ {
                board[i][j] += dice[i][k] * card[k][j]
            }
        }
    }

    auxiliary := make([]float64, length)
    copy(auxiliary, board[0])
    for true {
        for i := 0; i < length; i++ {
            probability[i] = 0
        }
        for i := 0; i < length; i++ {
            for j := 0; j < length; j++ {
                probability[i] += auxiliary[j] * board[j][i]
            }
        }

        isSame := true
        for i := 0; i < length; i++ {
            if math.Abs(probability[i] - auxiliary[i]) > 0.00001 {
                isSame = false
                break
            }
        }
        if isSame {
            return
        }
        copy(auxiliary, probability)
    }
}

func setSquares(squares []Square, probability []float64, size int) {
    for i := 0; i < size; i++ {
        squares[i] = Square{i, probability[i]}
    }
    adjust(squares)
    for i, value := range probability[size:] {
        if squares[0].value < value {
            squares[0].index = i + size
            squares[0].value = value
            adjust(squares)
        }
    }
}

func setJail(card [][]float64, index int) {
    card[index][10] = 1
    card[index][index] = 0
}

func setCommunityChest(card [][]float64, index int) {
    chance := float64(1) / 16
    card[index][0] = chance
    card[index][10] = chance
    card[index][index] -= chance * 2
}

func setChance(card [][]float64, index int) {
    chance := float64(1) / 16
    card[index][0] = chance
    card[index][10] = chance
    card[index][11] = chance
    card[index][24] = chance
    card[index][39] = chance
    card[index][5] = chance

    railway := 15
    utility := 12
    if 22 == index {
        railway = 25
        utility = 28
    } else if 36 == index {
        railway = 5
    }
    card[index][railway] += chance * 2
    card[index][utility] += chance
    card[index][index - 3] += chance
    card[index][index] -= chance * 10
}

func adjust(squares []Square) {
    pivot := 1
    if squares[1].value > squares[2].value {
        pivot = 2
    }

    if squares[0].value > squares[pivot].value {
        squares[0], squares[pivot] = squares[pivot], squares[0]
    }
}

type Square struct {
    index int
    value float64
}
