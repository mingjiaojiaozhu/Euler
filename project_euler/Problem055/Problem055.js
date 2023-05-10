function Problem055() {
    let target = 10000
    let decimal = new Decimal(100, 0)
    let auxiliary = Array(100)
    let result = 0
    for (let i = 1; i < target; ++i) {
        if (isLychrel(i, target, decimal, auxiliary)) {
            ++result
        }
    }
    console.log(result)
}

function isLychrel(value, target, decimal, auxiliary) {
    let count = 0
    while (count < 50) {
        if (value <= target) {
            value += reverseValue(value)
            if (isPalindrome(value)) {
                return false
            }
        } else {
            return isLychrelDecimal(value, count, decimal, auxiliary)
        }
        ++count
    }
    return true
}

function reverseValue(value) {
    let result = 0
    while (value) {
        result = result * 10 + value % 10
        value = Math.floor(value / 10)
    }
    return result
}

function isPalindrome(value) {
    let divisor = 1
    while (10 <= value / divisor) {
        divisor *= 10
    }

    while (value > 1) {
        let head = Math.floor(value / divisor)
        let tail = value % 10
        if (head !== tail) {
            return false
        }

        value = Math.floor(value % divisor / 10)
        divisor = Math.floor(divisor / 100)
    }
    return true
}

function isLychrelDecimal(value, count, decimal, auxiliary) {
    setValue(value, decimal)
    reverseDecimal(decimal, auxiliary)
    while (count < 50) {
        getSummation(decimal, auxiliary)
        if (isPalindromeDecimal(decimal, auxiliary)) {
            return false
        }
        ++count
    }
    return true
}

function setValue(value, decimal) {
    decimal.value.fill(0)
    decimal.length = 0
    while (value) {
        decimal.value[decimal.length] = value % 1e5
        ++decimal.length
        value = Math.floor(value / 1e5)
    }
}

function reverseDecimal(decimal, auxiliary) {
    auxiliary.fill(0)
    let index = 0
    let count = 0
    for (let i = decimal.length - 1; i >= 0; --i) {
        let value = decimal.value[i]
        let divisor = 1e5 / 10
        if (i === decimal.length - 1) {
            while (!Math.floor(value / divisor)) {
                divisor = Math.floor(divisor / 10)
            }
        }
        while (divisor) {
            auxiliary[index] += Math.floor(value / divisor) * Math.floor(Math.pow(10, count))
            value %= divisor
            divisor = Math.floor(divisor / 10)
            ++count
            if (5 === count) {
                ++index
                count = 0
            }
        }
    }
}

function getSummation(decimal, auxiliary) {
    for (let i = 0; i < decimal.length; ++i) {
        decimal.value[i] += auxiliary[i]
    }

    for (let i = 0; i < decimal.length; ++i) {
        if (decimal.value[i] >= 1e5) {
            decimal.value[i + 1] += Math.floor(decimal.value[i] / 1e5)
            decimal.value[i] %= 1e5
        }
    }
    if (0 !== decimal.value[decimal.length]) {
        ++decimal.length
    }
}

function isPalindromeDecimal(decimal, auxiliary) {
    reverseDecimal(decimal, auxiliary)
    for (let i = 0; i < decimal.length; ++i) {
        if (decimal.value[i] !== auxiliary[i]) {
            return false
        }
    }
    return true
}

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem055 : Problem055
};
