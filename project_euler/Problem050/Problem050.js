function Problem050() {
    let target = 1000000
    let primes = [2]
    let index = 3
    let summation = 2
    while (summation < target) {
        if (isPrime(index)) {
            primes.push(index)
            summation += index
        }
        index += 2
    }

    let length = primes.length
    for (let i = length - 1; i > 0; --i) {
        let value = summation - primes[i]
        if (isPrime(value)) {
            console.log(value)
            return
        }
        summation = value

        for (let j = i; j < length; ++j) {
            value += primes[j] - primes[j - i]
            if (isPrime(value) && value < target) {
                console.log(value)
                return
            }
        }
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
    Problem050 : Problem050
};
