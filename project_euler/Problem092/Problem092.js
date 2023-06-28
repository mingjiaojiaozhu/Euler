function Problem092() {
    let target = 10000000
    let border = 9 * 9 * Math.floor(Math.log10(target))
    let chains = new Set()
    let pivot = 89
    chains.add(pivot)

    let squares = Array(10)
    for (let i = 0; i < 10; ++i) {
        squares[i] = i * i
    }

    let result = 0
    for (let i = 1; i <= border; ++i) {
        if (getChains(i, chains, pivot, squares)) {
            ++result
        }
    }
    for (let i = border + 1; i < target; ++i) {
        if (chains.has(squareDigits(i, squares))) {
            ++result
        }
    }
    console.log(result)
}

function getChains(value, chains, pivot, squares) {
    if (chains.has(value) || pivot === value) {
        return true
    }
    if (1 === value) {
        return false
    }

    let result = getChains(squareDigits(value, squares), chains, pivot, squares)
    if (result) {
        chains.add(value)
    }
    return result
}

function squareDigits(value, squares) {
    let result = 0
    while (value) {
        result += squares[value % 10]
        value = Math.floor(value / 10)
    }
    return result
}

module.exports = {
    Problem092 : Problem092
};
