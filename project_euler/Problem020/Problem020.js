function Problem020() {
    let target = 100
    let decimal = new Decimal(target, 0)
    decimal.value[0] = target
    decimal.length = 1

    for (let i = target - 1; i > 1; --i) {
        getProduct(i, decimal)
    }

    let result = 0
    for (let value of decimal.value.slice(0, decimal.length)) {
        while (value > 0) {
            result += value % 10
            value = Math.floor(value / 10)
        }
    }
    console.log(result)
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

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem020 : Problem020
};
