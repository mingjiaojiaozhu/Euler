function Problem040() {
    let target = 1000000
    let borders = []
    let index = 0
    while (true) {
        let value = (Math.pow(10, index) * (9 * index - 1) + 1) / 9
        borders.push(value)
        if (value > target) {
            break
        }
        ++index
    }

    let result = 1
    while (target) {
        result *= getChampernowne(target, borders)
        target = Math.floor(target / 10)
    }
    console.log(result)
}

function getChampernowne(value, borders) {
    let index = getIndex(value, borders) - 1
    value -= borders[index] + 1
    let digit = Math.floor(Math.pow(10, index) + value / (index + 1))
    for (let i = value % (index + 1); i < index; ++i) {
        digit = Math.floor(digit / 10)
    }
    return digit % 10
}

function getIndex(value, borders) {
    let start = 0
    let end = borders.length - 1
    while (start <= end) {
        let current = start + ((end - start) >>> 1)
        if (borders[current] <= value) {
            start = current + 1
        } else {
            end = current - 1
        }
    }
    return start
}

module.exports = {
    Problem040 : Problem040
};
