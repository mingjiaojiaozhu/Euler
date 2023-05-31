function Problem072() {
    let target = 1000000
    let fractions = new Map()
    fractions.set(1, getSummation(1))
    let result = getFractions(target, fractions) - fractions.get(1)
    console.log(result)
}

function getFractions(target, fractions) {
    if (fractions.has(target)) {
        return fractions.get(target)
    }

    let index = 2
    let result = 0
    while (index <= target) {
        let step = Math.floor(target / Math.floor(target / index))
        result += (step - index + 1) * getFractions(Math.floor(target / step), fractions)
        index = step + 1
    }
    result = getSummation(target) - result
    fractions.set(target, result)
    return result
}

function getSummation(value) {
    return value * (value + 1) / 2
}

module.exports = {
    Problem072 : Problem072
};
