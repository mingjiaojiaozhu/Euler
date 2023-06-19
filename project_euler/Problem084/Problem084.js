function Problem084() {
    let target = 4
    let length = 40
    let dice = Array(length)
    for (let i = 0; i < length; ++i) {
        dice[i] = Array(length).fill(0)
    }
    setDice(dice, length, target)

    let card = Array(length)
    for (let i = 0; i < length; ++i) {
        card[i] = Array(length).fill(0)
    }
    setCard(card, length)

    let probability = Array(length)
    setProbability(probability, dice, card, length)

    let size = 3
    let squares = Array(size)
    setSquares(squares, probability, size)

    let result
    if (squares[1].value > squares[2].value) {
        result = squares[1].index * 100 + squares[2].index
    } else {
        result = squares[2].index * 100 + squares[1].index
    }
    result = result * 100 + squares[0].index
    console.log(result)
}

function setDice(dice, length, target) {
    let border = (target << 1) - 1
    let chances = Array(border)

    let start = 0
    let end = border - 1
    let count = 1
    let total = target * target
    while (start < end) {
        let chance = count / total
        chances[start] = chance
        chances[end] = chance
        ++count
        ++start
        --end
    }
    chances[start] = count / total

    for (let i = length - border - 2; i >= 0; --i) {
        for (let j = 0; j < border; ++j) {
            dice[i][i + j + 2] = chances[j]
        }
    }
    for (let i = length - border - 1; i < length - 2; ++i) {
        for (let j = length - i - 3; j >= 0; --j) {
            dice[i][i + j + 2] = chances[j]
        }
        for (let j = length - i - 2; j < border; ++j) {
            dice[i][i + j - length + 2] = chances[j]
        }
    }
    for (let i = length - 2; i < length; ++i) {
        for (let j = 0; j < border; ++j) {
            dice[i][i + j - length + 2] = chances[j]
        }
    }
}

function setCard(card, length) {
    for (let i = 0; i < length; ++i) {
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

function setProbability(probability, dice, card, length) {
    let board = Array(length)
    for (let i = 0; i < length; ++i) {
        board[i] = Array(length).fill(0)
    }
    for (let i = 0; i < length; ++i) {
        for (let j = 0; j < length; ++j) {
            for (let k = 0; k < length; ++k) {
                board[i][j] += dice[i][k] * card[k][j]
            }
        }
    }

    let auxiliary = board[0].slice()
    while (true) {
        probability.fill(0)
        for (let i = 0; i < length; ++i) {
            for (let j = 0; j < length; ++j) {
                probability[i] += auxiliary[j] * board[j][i]
            }
        }

        let isSame = true
        for (let i = 0; i < length; ++i) {
            if (Math.abs(probability[i] - auxiliary[i]) > 0.00001) {
                isSame = false
                break
            }
        }
        if (isSame) {
            return
        }
        auxiliary = probability.slice()
    }
}

function setSquares(squares, probability, size) {
    for (let i = 0; i < size; ++i) {
        squares[i] = new Square(i, probability[i])
    }
    adjust(squares)
    for (let [i, value] of probability.slice(size).entries()) {
        if (squares[0].value < value) {
            squares[0].index = i + size
            squares[0].value = value
            adjust(squares)
        }
    }
}

function setJail(card, index) {
    card[index][10] = 1
    card[index][index] = 0
}

function setCommunityChest(card, index) {
    let chance = 1 / 16
    card[index][0] = chance
    card[index][10] = chance
    card[index][index] -= chance * 2
}

function setChance(card, index) {
    let chance = 1 / 16
    card[index][0] = chance
    card[index][10] = chance
    card[index][11] = chance
    card[index][24] = chance
    card[index][39] = chance
    card[index][5] = chance

    let railway = 15
    let utility = 12
    if (22 === index) {
        railway = 25
        utility = 28
    } else if (36 === index) {
        railway = 5
    }
    card[index][railway] += chance * 2
    card[index][utility] += chance
    card[index][index - 3] += chance
    card[index][index] -= chance * 10
}

function adjust(squares) {
    let pivot = 1
    if (squares[1].value > squares[2].value) {
        pivot = 2
    }

    if (squares[0].value > squares[pivot].value) {
        let index = squares[0].index
        let value = squares[0].value
        squares[0].index = squares[pivot].index
        squares[0].value = squares[pivot].value
        squares[pivot].index = index
        squares[pivot].value = value
    }
}

function Square(index, value) {
    this.index = index
    this.value = value
}

module.exports = {
    Problem084 : Problem084
};
