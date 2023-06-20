function Problem035() {
    let target = 1000000
    let length = (target + 1) >>> 1
    let primes = Array(length).fill(true)
    primes[0] = false

    let border = Math.floor(Math.sqrt(target))
    for (let i = 3; i <= border; i += 2) {
        if (primes[i >>> 1]) {
            for (let j = i * i >>> 1; j < length; j += i) {
                primes[j] = false
            }
        }
    }

    let result = 13
    for (let i = 101; i < target; i += 2) {
        if (primes[i >>> 1] && checkDigits(i) && isCircular(i, primes)) {
            ++result
        }
    }
    console.log(result)
}

function checkDigits(value) {
    while (value) {
        let remainder = value % 10
        if (1 !== remainder && 3 !== remainder && 7 !== remainder && 9 !== remainder) {
            return false
        }
        value = Math.floor(value / 10)
    }
    return true
}

function isCircular(value, primes) {
    let divisor = 1
    let length = 1
    while (value / divisor >= 10) {
        divisor *= 10
        ++length
    }

    for (let i = 1; i < length; ++i) {
        value = (value % 10) * divisor + Math.floor(value / 10)
        if (!primes[value >>> 1]) {
            return false
        }
    }
    return true
}

module.exports = {
    Problem035 : Problem035
};
