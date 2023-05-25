function Problem069() {
    let target = 1000000
    let index = 3
    let result = 2
    while (true) {
        if (isPrime(index)) {
            if (result * index >= target) {
                console.log(result)
                return
            }
            result *= index
        }
        index += 2
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
    Problem069 : Problem069
};
