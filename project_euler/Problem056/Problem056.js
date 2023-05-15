function Problem056() {
    let target = 100
    let decimal = new Decimal(target, 0)
    let result = 0
    for (let i = 2; i < target; ++i) {
        decimal.value.fill(0)
        setValue(i, decimal)
        for (let j = 2; j < target; ++j) {
            getProduct(i, decimal)
            result = getDigital(decimal, result)
        }
    }
    console.log(result)
}

function setValue(value, decimal) {
    decimal.value[0] = value
    decimal.length = 1
}

function getProduct(value, decimal) {
    for (let i = 0; i < decimal.length; ++i) {
        decimal.value[i] *= value
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

function getDigital(decimal, pivot) {
    let result = 0
    for (let value of decimal.value.slice(0, decimal.length)) {
        while (value) {
            result += value % 10
            value = Math.floor(value / 10)
        }
    }
    return Math.max(result, pivot)
}

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem056 : Problem056
};
