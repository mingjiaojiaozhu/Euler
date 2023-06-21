function Problem087() {
    let target = 50000000
    let primes = Array(3)
    for (let i = 0; i < 3; ++i) {
        primes[i] = []
    }
    getPrimes(primes, 2, 3)

    let borders = [Math.floor(Math.sqrt(target)), Math.floor(Math.pow(target, 1 / 3)), Math.floor(Math.pow(target, 1 / 4))]
    let index = 3
    for (let i = 2; i >= 0; --i) {
        let size = i + 1
        while (index < borders[i]) {
            if (isPrime(index)) {
                getPrimes(primes, index, size)
            }
            index += 2
        }
    }

    let summations = new Set()
    for (let prime of primes[2]) {
        let pivot = target - prime
        let border = getIndex(pivot, primes[1])
        for (let i = 0; i < border; ++i) {
            let value = primes[1][i]
            let end = getIndex(pivot - value, primes[0])
            for (let j = 0; j < end; ++j) {
                summations.add(prime + value + primes[0][j])
            }
        }
    }
    console.log(summations.size)
}

function getPrimes(primes, pivot, size) {
    let value = pivot
    for (let i = 0; i < size; ++i) {
        value *= pivot
        primes[i].push(value)
    }
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

function getIndex(value, primes) {
    let start = 0
    let end = primes.length - 1
    while (start <= end) {
        let current = start + ((end - start) >>> 1)
        if (primes[current] <= value) {
            start = current + 1
        } else {
            end = current - 1
        }
    }
    return start
}

module.exports = {
    Problem087 : Problem087
};
