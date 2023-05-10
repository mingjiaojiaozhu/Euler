function Problem023() {
    let start = 24
    let end = 28123
    let abundants = new Set()
    for (let i = start >>> 1; i <= start; ++i) {
        if (isAbundant(i)) {
            abundants.add(i)
        }
    }

    let result = start * (start - 1) >>> 1
    for (let i = start + 1; i <= end; ++i) {
        let isNonAbundant = true
        for (let abundant of abundants) {
            if (abundants.has(i - abundant)) {
                isNonAbundant = false
                break
            }
        }
        if (isNonAbundant) {
            result += i
        }

        if (isAbundant(i)) {
            abundants.add(i)
        }
    }
    console.log(result)
}

function isAbundant(value) {
    let border = Math.floor(Math.sqrt(value))
    let summation = 1
    for (let i = 2; i < border; ++i) {
        if (!(value % i)) {
            summation += i + value / i
        }
    }
    if (!(value % border)) {
        summation += border
        if (value !== border * border) {
            summation += value / border
        }
    }
    return summation > value
}

module.exports = {
    Problem023 : Problem023
};
