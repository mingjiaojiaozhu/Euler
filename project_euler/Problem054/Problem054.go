package project_euler

import (
    "bufio"
    "fmt"
    "io"
    "os"
    "sort"
    "strings"
)

func Problem054() {
    fileName := "poker.txt"
    players := [2]Player{}
    for i := 0; i < 2; i++ {
        players[i] = Player{make([]int, 5), make(map[string]bool), 0, make([]int, 0)}
    }
    counts := make([]int, 2)
    pairs := make([]int, 2)

    file, _ := os.Open(fileName)
    handle := bufio.NewReader(file)
    result := 0
    for true {
        line, _, err := handle.ReadLine()
        if io.EOF == err {
            break
        }

        elements := strings.Split(strings.Replace(string(line), "\n", "", -1), " ")
        setCards(&players[0], elements, 0, counts, pairs)
        setCards(&players[1], elements, 5, counts, pairs)
        if isWinner(players) {
            result++
        }
    }
    file.Close()
    fmt.Println(result)
}

func setCards(player *Player, elements []string, start int, counts []int, pairs []int)  {
    player.suits = make(map[string]bool)
    player.ranks = make([]int, 0)

    for i := 0; i < 5; i++ {
        value := elements[start + i]
        player.value[i] = getValue(value[:1])
        player.suits[value[1:]] = true
    }
    sort.Ints(player.value)
    setHead(player, counts, pairs)
}

func isWinner(players [2]Player) bool {
    if players[0].hand != players[1].hand {
        return players[0].hand < players[1].hand
    }

    length := len(players[0].ranks)
    for i := 0; i < length; i++ {
        if players[0].ranks[i] != players[1].ranks[i] {
            return players[0].ranks[i] > players[1].ranks[i]
        }
    }
    return true
}

func getValue(value string) int {
    if "A" == value {
        return 14
    }
    if "K" == value {
        return 13
    }
    if "Q" == value {
        return 12
    }
    if "J" == value {
        return 11
    }
    if "T" == value {
        return 10
    }
    return int(value[0] - '0')
}

func setHead(player *Player, counts []int, pairs []int) {
    for i := 0; i < 2; i++ {
        counts[i] = 0
        pairs[i] = 0
    }
    isStraight := true
    index := 0
    isPair := false
    for i := 1; i < 5; i++ {
        if 1 != player.value[i] - player.value[i - 1] {
            isStraight = false
        }

        if player.value[i] == player.value[i - 1] {
            counts[index]++
            pairs[index] = player.value[i]
            isPair = true
        } else {
            if isPair {
                index++
            }
            isPair = false
        }
    }

    isFlush := 1 == len(player.suits)
    if isStraight {
        if isFlush {
            player.hand = 0
        } else {
            player.hand = 4
        }
        player.ranks = append(player.ranks, player.value[4])
        return
    }

    if 3 == counts[0] {
        player.hand = 1
        player.ranks = append(player.ranks, pairs[0])
        return
    }
    if 2 == counts[0] || 2 == counts[1] {
        if 1 == counts[0] || 1 == counts[1] {
            player.hand = 2
        } else {
            player.hand = 5
        }
        if 2 == counts[0] {
            player.ranks = append(player.ranks, pairs[0])
        } else {
            player.ranks = append(player.ranks, pairs[1])
        }
        return
    }
    if 1 == counts[0] {
        if 1 == counts[1] {
            player.hand = 6
            player.ranks = append(player.ranks, pairs[1])
        } else {
            player.hand = 7
        }
        player.ranks = append(player.ranks, pairs[0])
        for i := 4; i >= 0; i-- {
            if player.value[i] != pairs[0] && player.value[i] != pairs[1] {
                player.ranks = append(player.ranks, player.value[i])
            }
        }
        return
    }

    if isFlush {
        player.hand = 3
    } else {
        player.hand = 8
    }
    for i := 4; i >= 0; i-- {
        player.ranks = append(player.ranks, player.value[i])
    }
}

type Player struct {
    value []int
    suits map[string]bool
    hand int
    ranks []int
}
