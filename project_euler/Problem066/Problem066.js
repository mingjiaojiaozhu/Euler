function Problem066() {
    let target = 1000
    let factors = []
    let previous = new Decimal(100, 0)
    let current = new Decimal(100, 0)
    let auxiliary = new Decimal(100, 0)

    let result = 0
    let pivot = new Decimal(100, 0)
    for (let i = 5; i <= target; ++i) {
        if (getSolution(i, factors, previous, current, auxiliary) && isGreater(current, pivot)) {
            swapDecimal(current, pivot)
            result = i
        }
    }
    console.log(result)
}

function getSolution(value, factors, previous, current, auxiliary) {
    factors.length = 0
    let start = getPeriod(value, factors)
    if (!start) {
        return false;
    }

    setValue(0, previous)
    setValue(1, current)
    getConvergents(previous, current, factors)
    if (0 !== (factors.length & 1)) {
        return true;
    }

    setValue(1, previous)
    setValue(start, auxiliary)
    getConvergents(previous, auxiliary, factors)
    swapDecimal(previous, current)
    getProduct(previous, auxiliary, current)
    getDouble(current)
    return true
}

function isGreater(current, pivot) {
    if (current.length !== pivot.length) {
        return current.length > pivot.length
    }

    for (let i = current.length - 1; i >= 0; --i) {
        if (current.value[i] !== pivot.value[i]) {
            return current.value[i] > pivot.value[i]
        }
    }
    return false
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

function getPeriod(value, factors) {
    let auxiliary = Math.sqrt(value)
    if (Math.abs(Math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001) {
        return 0
    }

    let initial = Math.floor(auxiliary)
    let pivot = initial << 1
    let current = initial
    let offset = 0
    let factor = 1
    while (current !== pivot) {
        offset = current * factor - offset
        factor = Math.floor((value - offset * offset) / factor)
        current = Math.floor((initial + offset) / factor)
        factors.push(current)
    }
    factors.pop()
    return initial
}

function setValue(value, decimal) {
    decimal.value.fill(0)
    decimal.value[0] = value
    decimal.length = 1
}

function getConvergents(previous, current, factors) {
    for (let factor of factors) {
        getSummation(current, factor, previous);
        swapDecimal(previous, current);
    }
}

function getProduct(multiplicand, multiplier, product) {
    for (let i = 0; i < multiplicand.length; ++i) {
        for (let j = 0; j < multiplier.length; ++j) {
            let value = multiplicand.value[i] * multiplier.value[j]
            let index = i + j
            product.value[index] += value % 1e5
            product.value[index + 1] += Math.floor(value / 1e5)
        }
    }
    product.length = multiplicand.length + multiplier.length - 1
    carry(product)
}

function getDouble(decimal) {
    for (let i = 0; i < decimal.length; ++i) {
        decimal.value[i] <<= 1
    }
    carry(decimal)
}

function getSummation(decimal, factor, summation) {
    for (let i = 0; i < decimal.length; ++i) {
        summation.value[i] += decimal.value[i] * factor
    }
    carry(summation)
}

function carry(decimal) {
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
    Problem066 : Problem066
};
