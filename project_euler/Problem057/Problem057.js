function Problem057() {
    let target = 1000
    let numerator = new Decimal(100, 0)
    let denominator = new Decimal(100, 0)
    setValue(3, numerator)
    setValue(2, denominator)

    let result = 0
    for (let i = 2; i < target; ++i) {
        getSummation(denominator, numerator)
        getSummation(numerator, denominator)
        swapDecimal(numerator, denominator)
        if (numerator.length > denominator.length || getDigits(numerator.value[numerator.length - 1]) > getDigits(denominator.value[denominator.length - 1])) {
            ++result
        }
    }
    console.log(result)
}

function setValue(value, decimal) {
    decimal.value[0] = value
    decimal.length = 1
}

function getSummation(decimal, summation) {
    for (let i = 0; i < decimal.length; ++i) {
        summation.value[i] += decimal.value[i]
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

function swapDecimal(numerator, denominator) {
    let length = Math.max(numerator.length, denominator.length)
    for (let i = 0; i < length; ++i) {
        numerator.value[i] ^= denominator.value[i]
        denominator.value[i] ^= numerator.value[i]
        numerator.value[i] ^= denominator.value[i]
    }
    numerator.length ^= denominator.length
    denominator.length ^= numerator.length
    numerator.length ^= denominator.length
}

function getDigits(value) {
    let result = 0
    while (value) {
        ++result
        value = Math.floor(value / 10)
    }
    return result
}

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem057 : Problem057
};
