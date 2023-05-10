function Problem016() {
    let target = 1000
    let length = Math.floor((target + 4) / 5)
    let decimal = new Decimal(length, 0)
    let auxiliary = Array(length)
    getPower(target, decimal, auxiliary)

    let result = 0
    for (let value of decimal.value.slice(0, decimal.length)) {
        while (value > 0) {
            result += value % 10
            value = Math.floor(value / 10)
        }
    }
    console.log(result)
}

function getPower(value, decimal, auxiliary) {
    if (value < 8) {
        decimal.value[0] = Math.pow(2, value)
        decimal.length = 1
        return
    }

    getPower(value >>> 1, decimal, auxiliary)
    getSquare(decimal, auxiliary)
    if (0 !== (value & 1)) {
        getDouble(decimal)
    }
}

function getSquare(decimal, auxiliary) {
    auxiliary.fill(0)
    for (let i = 0; i < decimal.length; ++i) {
        for (let j = 0; j < decimal.length; ++j) {
            let result = decimal.value[i] * decimal.value[j]
            let index = i + j
            auxiliary[index] += result % 1e5
            auxiliary[index + 1] += Math.floor(result / 1e5)
        }
    }

    decimal.length = (decimal.length << 1) - 1
    for (let i = 0; i < decimal.length; ++i) {
        if (auxiliary[i] >= 1e5) {
            auxiliary[i + 1] += Math.floor(auxiliary[i] / 1e5)
            auxiliary[i] %= 1e5
        }
    }
    if (auxiliary[decimal.length]) {
        ++decimal.length
    }
    decimal.value = auxiliary.slice()
}

function getDouble(decimal) {
    for (let i = 0; i < decimal.length; ++i) {
        decimal.value[i] <<= 1
    }

    for (let i = 0; i < decimal.length; ++i) {
        if (decimal.value[i] >= 1e5) {
            decimal.value[i + 1] += Math.floor(decimal.value[i] / 1e5)
            decimal.value[i] %= 1e5
        }
    }
    if (decimal.value[decimal.length]) {
        ++decimal.length
    }
}

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem016 : Problem016
};
