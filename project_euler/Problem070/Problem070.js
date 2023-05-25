function Problem070() {
    let target = 10000000
    let pivot = Math.floor(Math.sqrt(target))
    let start = getPreviousPrime(pivot)
    let end = getNextPrime(pivot)
    let primes = [end]
    let pivots = Array(10)
    let digits = Array(10)
    let result = 0
    while (true) {
        for (let prime of primes) {
            getDigits(start * prime, pivots)
            getDigits((start - 1) * (prime - 1), digits)
            if (checkDigits(pivots, digits)) {
                result = start * prime
            }
        }

        end = getNextPrime(primes[primes.length - 1])
        while (start * end < target) {
            primes.push(end)
            getDigits(start * end, pivots)
            getDigits((start - 1) * (end - 1), digits)
            if (checkDigits(pivots, digits)) {
                result = start * end
            }
            end = getNextPrime(end)
        }

        if (result) {
            console.log(result)
            return
        }
        start = getPreviousPrime(start)
    }
}

function getPreviousPrime(value) {
    if (0 === (value & 1)) {
        --value
    } else {
        value -= 2
    }

    while (!isPrime(value)) {
        value -= 2
    }
    return value
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

function getDigits(value, digits) {
    digits.fill(0)
    while (value) {
        ++digits[value % 10]
        value = Math.floor(value / 10)
    }
}

function checkDigits(pivots, digits) {
    for (let i = 0; i < 10; ++i) {
        if (pivots[i] !== digits[i]) {
            return false
        }
    }
    return true
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

module.exports = {
    Problem070 : Problem070
};
