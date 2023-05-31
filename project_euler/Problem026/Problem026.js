function Problem026() {
    let target = 1000
    let remainders = []
    let result = 0
    let pivot = 0
    for (let i = target - 1; i >= 7; i -= 2) {
        if (isPrime(i)) {
            let count = getDigit(i, remainders)
            if (pivot < count) {
                pivot = count
                result = i
            }
            if (count === i - 1) {
                break
            }
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

function getDigit(value, remainders) {
    remainders.length = 0
    let remainder = 1
    while (true) {
        remainders.push(remainder)
        remainder = remainder * 10 % value
        let index = remainders.indexOf(remainder)
        if (-1 !== index) {
            return remainders.length - index
        }
    }
}

module.exports = {
    Problem026 : Problem026
};
