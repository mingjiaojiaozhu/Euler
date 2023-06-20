function Problem010() {
    let target = 2000000
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

    let result = 2
    for (let [i, prime] of primes.slice(1).entries()) {
        if (prime) {
            result += ((i + 1) << 1) + 1
        }
    }
    console.log(result)
}

module.exports = {
    Problem010 : Problem010
};
