function Problem014() {
    let target = 1000000
    let chains = Array(target).fill(-1)
    chains[0] = 1
    chains[1] = 2

    for (let i = 3; i <= target; ++i) {
        getCollatz(i, chains, target)
    }

    let result = 0
    let pivot = 0
    for (let [i, chain] of chains.slice(2).entries()) {
        if (pivot < chain) {
            pivot = chain
            result = i + 3
        }
    }
    console.log(result)
}

function getCollatz(value, chains, length) {
    if (value <= length && -1 !== chains[value - 1]) {
        return chains[value - 1]
    }

    let result
    if (0 !== (value & 1)) {
        result = getCollatz(3 * value + 1, chains, length) + 1
    } else {
        result = getCollatz(value >>> 1, chains, length) + 1
    }
    if (value <= length) {
        chains[value - 1] = result
    }
    return result
}

module.exports = {
    Problem014 : Problem014
};
