function Problem037() {
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

    let result = 0
    for (let i = 11; i < target; i += 2) {
        if (primes[i >>> 1] && checkDigits(i) && isTruncatable(i, primes)) {
            result += i
        }
    }
    console.log(result)
}

function checkDigits(value) {
    let remainder = value % 10
    if (3 !== remainder && 7 !== remainder) {
        return false
    }

    value = Math.floor(value / 10)
    while (value >= 10) {
        remainder = value % 10
        if (1 !== remainder && 3 !== remainder && 7 !== remainder && 9 !== remainder) {
            return false
        }
        value = Math.floor(value / 10)
    }
    return 2 === value || 3 === value || 5 === value || 7 === value
}

function isTruncatable(value, primes) {
    let divisor = 1
    while (value / divisor >= 10) {
        divisor *= 10
    }

    let head = Math.floor(value / 10)
    let tail = value % divisor
    while (head && tail) {
        if ((2 !== head && !primes[head >>> 1]) || !primes[tail >>> 1]) {
            return false
        }

        divisor = Math.floor(divisor / 10)
        head = Math.floor(head / 10)
        tail %= divisor
    }
    return true
}

module.exports = {
    Problem037 : Problem037
};
