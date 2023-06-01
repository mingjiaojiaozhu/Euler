function Problem077() {
    let target = 5000
    let primes = [2, 3]
    let result = 11
    while (getWays(result, primes) <= target) {
        ++result
    }
    console.log(result)
}

function getWays(target, primes) {
    let index = primes[primes.length - 1] + 2
    while (index <= target) {
        if (isPrime(index)) {
            primes.push(index)
        }
        index += 2
    }

    let ways = Array(target + 1).fill(0)
    ways[0] = 1
    for (let prime of primes) {
        for (let i = prime; i <= target; ++i) {
            ways[i] += ways[i - prime]
        }
    }
    return ways[target]
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
    Problem077 : Problem077
};
