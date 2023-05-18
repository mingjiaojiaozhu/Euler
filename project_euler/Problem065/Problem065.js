function Problem065() {
    let target = 100
    let previous = new Decimal(100, 0)
    let current = new Decimal(100, 0)
    setValue(1, previous)
    setValue(2, current)
    for (let i = 2; i <= target; ++i) {
        let factor = 1
        if (!(i % 3)) {
            factor = (i << 1) / 3
        }
        getSummation(current, factor, previous)
        swapDecimal(previous, current)
    }

    let result = 0
    for (let value of current.value.slice(0, current.length)) {
        while (value) {
            result += value % 10
            value = Math.floor(value / 10)
        }
    }
    console.log(result)
}

function setValue(value, decimal) {
    decimal.value[0] = value
    decimal.length = 1
}

function getSummation(decimal, factor, summation) {
    for (let i = 0; i < decimal.length; ++i) {
        summation.value[i] += decimal.value[i] * factor
    }

    for (let i = 0; i < summation.length; ++i) {
        if (summation.value[i] >= 1e5) {
            summation.value[i + 1] += Math.floor(summation.value[i] / 1e5)
            summation.value[i] %= 1e5
        }
    }
    if (summation.value[summation.length]) {
        ++summation.length
    }
}

function swapDecimal(previous, current) {
    let length = Math.max(previous.length, current.length)
    for (let i = 0; i < length; ++i) {
        previous.value[i] ^= current.value[i]
        current.value[i] ^= previous.value[i]
        previous.value[i] ^= current.value[i]
    }
    previous.length ^= current.length
    current.length ^= previous.length
    previous.length ^= current.length
}

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem065 : Problem065
};
