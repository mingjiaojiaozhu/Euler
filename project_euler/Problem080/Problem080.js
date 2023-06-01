function Problem080() {
    let target = 100
    let current = new Decimal(100, 0)
    let auxiliary = new Decimal(100, 0)
    let length = Math.floor((target + 2) / 5) + 1
    let pivot = Math.pow(10, (target + 2) % 5)
    let result = 0
    for (let i = 2; i <= target; ++i) {
        if (Math.abs(Math.floor(Math.sqrt(i) + 0.5) - Math.sqrt(i)) > 0.00000001) {
            getDigits(i, current, auxiliary, length, pivot)
            result += getSummation(current, pivot)
        }
    }
    console.log(result)
}

function getDigits(value, current, auxiliary, length, pivot) {
    setValue(5, current)
    setValue(value * 5, auxiliary)
    while (checkLength(current, length, pivot)) {
        if (!isGreater(current, auxiliary)) {
            getDifference(current, auxiliary)
            current.value[0] += 10
            carry(current)
        } else {
            getProduct(auxiliary, 100)
            fillZero(current)
        }
    }
}

function getSummation(current, pivot) {
    let result = addDigit(Math.floor(Math.floor(current.value[0] / pivot) / 10))
    for (let i = 1; i < current.length; i++) {
        result += addDigit(current.value[i])
    }
    return result
}

function setValue(value, decimal) {
    decimal.value.fill(0)
    decimal.value[0] = value
    decimal.length = 1
}

function checkLength(current, length, pivot) {
    if (current.length < length) {
        return true
    }
    return current.value[length - 1] < pivot
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

function getDifference(decimal, difference) {
    for (let i = 0; i < decimal.length; ++i) {
        difference.value[i] -= decimal.value[i]
    }

    for (let i = 0; i < difference.length; ++i) {
        if (difference.value[i] < 0) {
            --difference.value[i + 1]
            difference.value[i] += 1e5
        }
    }
    while (!difference.value[difference.length - 1]) {
        --difference.length
    }
}

function getProduct(decimal, factor) {
    for (let i = 0; i < decimal.length; ++i) {
        decimal.value[i] *= factor
    }
    carry(decimal)
}

function fillZero(decimal) {
    let remainder = decimal.value[0] % 10
    decimal.value[0] -= remainder
    getProduct(decimal, 10)
    decimal.value[0] += remainder
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

function addDigit(value) {
    let result = 0
    while (value) {
        result += value % 10
        value = Math.floor(value / 10)
    }
    return result
}

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem080 : Problem080
};
