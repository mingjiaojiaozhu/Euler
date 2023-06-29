function Problem095() {
    let target = 1000000
    let divisors = Array(target).fill(-1)
    for (let i = 2; i <= target; ++i) {
        getDivisorSummation(i, divisors, target)
    }
    for (let i = 1; i < target; ++i) {
        divisors[i] -= i + 1
    }

    let result = 0
    let pivot = 0
    let chains = new Set()
    for (let i = 2; i <= target; ++i) {
        let count = getChain(i, divisors, chains, target)
        if (pivot < count) {
            pivot = count
            result = target
            for (let value of chains) {
                if (result > value) {
                    result = value
                }
            }
        }
    }
    console.log(result)
}

function getDivisorSummation(value, divisors, length) {
    if (-1 === divisors[value - 1]) {
        let index = value
        let count = 1
        while (index <= length) {
            divisors[index - 1] = (Math.pow(value, count + 1) - 1) / (value - 1)
            index *= value
            ++count
        }

        for (let i = Math.min(value - 1, Math.floor(length / value)); i >= 2; --i) {
            divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]
        }
    } else {
        for (let i = Math.min(value - 1, Math.floor(length / value)); i >= 2; --i) {
            if (isRelativelyPrime(value, i) && -1 === divisors[value * i - 1]) {
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]
            }
        }
    }
}

function getChain(value, divisors, chains, target) {
    chains.clear()
    chains.add(value)

    let pivot = value
    let count = 0
    while (true) {
        value = divisors[value - 1]
        if (pivot === value) {
            break
        }
        if (1 === value || value >= target || chains.has(value)) {
            return 0
        }

        chains.add(value)
        ++count
    }
    return count
}

function isRelativelyPrime(i, j) {
    while (i % j) {
        let auxiliary = i % j
        i = j
        j = auxiliary
    }
    return 1 === j
}

module.exports = {
    Problem095 : Problem095
};
