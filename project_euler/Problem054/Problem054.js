function Problem054() {
    let fileName = 'poker.txt'
    let players = Array(2)
    for (let i = 0; i < 2; ++i) {
        players[i] = new Player()
    }
    let counts = Array(2)
    let pairs = Array(2)

    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    let result = 0
    while (line = handle.next()) {
        let elements = line.toString().split(' ')
        setCards(players[0], elements, 0, counts, pairs)
        setCards(players[1], elements, 5, counts, pairs)
        if (isWinner(players)) {
            ++result
        }
    }
    console.log(result)
}

function setCards(player, elements, start, counts, pairs) {
    player.suits.clear()
    player.ranks.length = 0

    for (let i = 0; i < 5; ++i) {
        let value = elements[start + i]
        player.value[i] = getValue(value[0])
        player.suits.add(value[1])
    }
    player.value.sort(function(i, j) {return i - j})
    setHead(player, counts, pairs)
}

function isWinner(players) {
    if (players[0].hand !== players[1].hand) {
        return players[0].hand < players[1].hand
    }

    let length = players[0].ranks.length
    for (let i = 0; i < length; ++i) {
        if (players[0].ranks[i] !== players[1].ranks[i]) {
            return players[0].ranks[i] > players[1].ranks[i]
        }
    }
    return true
}

function getValue(value) {
    if ('A' === value) {
        return 14
    }
    if ('K' === value) {
        return 13
    }
    if ('Q' === value) {
        return 12
    }
    if ('J' === value) {
        return 11
    }
    if ('T' === value) {
        return 10
    }
    return Number(value)
}

function setHead(player, counts, pairs) {
    counts.fill(0)
    pairs.fill(0)
    let isStraight = true
    let index = 0
    let isPair = false
    for (let i = 1; i < 5; ++i) {
        if (1 !== player.value[i] - player.value[i - 1]) {
            isStraight = false
        }

        if (player.value[i] === player.value[i - 1]) {
            ++counts[index]
            pairs[index] = player.value[i]
            isPair = true
        } else {
            if (isPair) {
                ++index
            }
            isPair = false
        }
    }

    let isFlush = (1 === player.suits.size)
    if (isStraight) {
        if (isFlush) {
            player.hand = 0
        } else {
            player.hand = 4
        }
        player.ranks.push(player.value[4])
        return
    }

    if (3 === counts[0]) {
        player.hand = 1
        player.ranks.push(pairs[0])
        return
    }
    if (2 === counts[0] || 2 === counts[1]) {
        if (1 === counts[0] || 1 === counts[1]) {
            player.hand = 2
        } else {
            player.hand = 5
        }
        if (2 === counts[0]) {
            player.ranks.push(pairs[0])
        } else {
            player.ranks.push(pairs[1])
        }
        return
    }
    if (1 === counts[0]) {
        if (1 === counts[1]) {
            player.hand = 6
            player.ranks.push(pairs[1])
        } else {
            player.hand = 7
        }
        player.ranks.push(pairs[0])
        for (let i = 4; i >= 0; --i) {
            if (player.value[i] !== pairs[0] && player.value[i] !== pairs[1]) {
                player.ranks.push(player.value[i])
            }
        }
        return
    }

    if (isFlush) {
        player.hand = 3
    } else {
        player.hand = 8
    }
    for (let i = 4; i >= 0; --i) {
        player.ranks.push(player.value[i])
    }
}

function Player() {
    this.value = Array(5)
    this.suits = new Set()
    this.hand = 0
    this.ranks = []
}

module.exports = {
    Problem054 : Problem054
};
