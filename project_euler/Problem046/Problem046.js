function Problem046() {
    let primes = new Set([2])
    let result = 3
    while (true) {
        if (isPrime(result)) {
            primes.add(result)
        } else {
            let border = Math.floor(Math.sqrt((result - 1) >>> 1))
            let isGoldbach = false
            for (let i = 1; i <= border; ++i) {
                if (primes.has(result - (i * i << 1))) {
                    isGoldbach = true
                    break
                }
            }
            if (!isGoldbach) {
                console.log(result)
                return
            }
        }
        result += 2
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

module.exports = {
    Problem046 : Problem046
};
