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
    Problem007 : Problem007
};
