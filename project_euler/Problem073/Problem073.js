function Problem073() {
    let target = 12000
    let fractions = new Map()
    fractions.set(1, getCount(1))
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
    result = getCount(target) - result
    fractions.set(target, result)
    return result
}

function getCount(value) {
    let quotient = Math.floor(value / 6)
    let remainder = value % 6
    if (5 === remainder) {
        return quotient * (quotient * 3 - 2 + remainder) + 1
    }
    return quotient * (quotient * 3  - 2 + remainder)
}

module.exports = {
    Problem073 : Problem073
};
