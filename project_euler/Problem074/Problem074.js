function Problem074() {
    let target = 60
    let border = 1000000
    let step = Math.floor(Math.log10(border))
    let permutations = []
    for (let i = 1; i < 10; ++i) {
        permutations.push(i)
    }
    let chains = new Set()
    let terms = new Map()
    let factorials = Array(10)
    factorials[0] = 1
    for (let i = 1; i < 10; ++i) {
        factorials[i] = factorials[i - 1] * i
    }
    let counts = Array(10)
    let auxiliary = []
    let result = 0
    for (let value of permutations) {
        if (target === getTerms(value, chains, terms, factorials, counts)) {
            result += getPermutations(value, factorials, counts)
        }
    }
    for (let i = 1; i < step; ++i) {
        getDigits(permutations, auxiliary)
        for (let value of permutations) {
            if (target === getTerms(value, chains, terms, factorials, counts)) {
                result += getPermutations(value, factorials, counts)
            }
        }
    }
    console.log(result)
}

function getTerms(value, chains, terms, factorials, counts) {
    chains.clear()
    let pivot = value
    let result
    while (true) {
        if (terms.has(value)) {
            result = chains.size + terms.get(value)
            break
        }
        if (chains.has(value)) {
            result = chains.size
            break
        }

        chains.add(value)
        value = getSummation(value, factorials, counts)
    }
    terms.set(pivot, result)
    return result
}

function getPermutations(value, factorials, counts) {
    let length = 0
    let exists0 = false
    counts.fill(0)
    while (value) {
        ++length
        let remainder = value % 10
        if (!remainder) {
            exists0 = true
        }
        ++counts[remainder]
        value = Math.floor(value / 10)
    }

    let result = factorials[length]
    if (exists0) {
        result = result * (length - 1) / length
    }
    for (let count of counts) {
        if (1 !== count) {
            result /= factorials[count]
        }
    }
    return result
}

function getDigits(permutations, auxiliary) {
    auxiliary = auxiliary.concat(permutations)
    permutations.length = 0
    for (let value of auxiliary) {
        let remainder = value % 10
        for (let i = 0; i <= remainder; ++i) {
            permutations.push(value * 10 + i)
        }
    }
    auxiliary.length = 0
}

function getSummation(value, factorials, counts) {
    let result = 0
    while (value) {
        result += factorials[value % 10]
        value = Math.floor(value / 10)
    }

    counts.fill(0)
    while (result) {
        ++counts[9 - result % 10]
        result = Math.floor(result / 10)
    }

    for (let [i, count] of counts.entries()) {
        for (let j = 0; j < count; ++j) {
            result = result * 10 + 9 - i
        }
    }
    return result
}

module.exports = {
    Problem074 : Problem074
};
