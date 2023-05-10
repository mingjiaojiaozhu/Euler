function Problem007() {
    let target = 10001
    let result = 1
    let count = 1
    while (count < target) {
        result += 2
        if (isPrime(result)) {
            ++count
        }
    }
    console.log(result)
}

function isPrime(value) {
    if (0 === (value & 1)) {
        return 2 === value
    }

    let border = Math.floor(Math.sqrt(value))
    for (let i = 3; i <= border; i += 2) {
        if (!(value % i)) {
            return false
        }
    }
    return 1 !== value
}

module.exports = {
    Problem007 : Problem007
};
