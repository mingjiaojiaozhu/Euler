function Problem051() {
    let target = 8
    let digits = Array(3)
    for (let i = 0; i < 3; ++i) {
        digits[i] = []
    }
    let steps = []
    let auxiliary = []

    let result = 1111
    while (true) {
        result = getNextPrime(result)
        if (checkDigits(result, digits) && checkPrimeFamily(result, target, digits, steps, auxiliary)) {
            console.log(result)
            return
        }
    }
}

function getNextPrime(value) {
    if (0 === (value & 1)) {
        ++value
    } else {
        value += 2
    }

    while (!isPrime(value)) {
        value += 2
    }
    return value
}

function checkDigits(value, digits) {
    for (let i = 0; i < 3; ++i) {
        digits[i] = []
    }

    value = Math.floor(value / 10)
    let count = 1
    while (value) {
        let remainder = value % 10
        if (!remainder || 1 === remainder || 2 === remainder) {
            digits[remainder].push(count)
        }
        value = Math.floor(value / 10)
        ++count
    }

    for (let digit of digits) {
        if (digit.length >= 3) {
            return true
        }
    }
    return false
}

function checkPrimeFamily(pivot, target, digits, steps, auxiliary) {
    let isFamily = false
    for (let [i, digit] of digits.entries()) {
        if (digit.length < 3) {
            continue
        }

        steps = []
        auxiliary = []
        combination(digit, 0, 3, digit.length, steps, auxiliary)
        for (let step of steps) {
            let count = 10 - target - i
            let value = pivot
            for (let j = i; j < 9; ++j) {
                value += step
                if (!isPrime(value)) {
                    --count
                }
                if (count < 0) {
                    break
                }
            }
            isFamily = !count
        }
    }
    return isFamily
}

function isPrime(value) {
    if (1 !== value % 6 && 5 !== value % 6) {
        return 2 === value || 3 === value
    }

    let border = Math.floor(Math.sqrt(value))
    for (let i = 5; i <= border; i += 6) {
        if (!(value % i) || !(value % (i + 2))) {
            return false
        }
    }
    return 1 !== value
}

function combination(digits, start, count, length, steps, auxiliary) {
    if (count === auxiliary.length) {
        let value = 0
        for (let digit of auxiliary) {
            value += digit
        }
        steps.push(value)
        return
    }

    for (let i = start; i < length; ++i) {
        auxiliary.push(Math.pow(10, digits[i]))
        combination(digits, i + 1, count, length, steps, auxiliary)
        auxiliary.pop()
    }
}

module.exports = {
    Problem051 : Problem051
};
