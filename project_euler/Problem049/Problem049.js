function Problem049() {
    let target = 3330
    let other = 1487
    let terms = Array(2)
    let digits = Array(10)
    for (let i = 10000 - (target << 1) - 1; i > 1000; i -= 2) {
        if (isPrime(i) && i !== other) {
            terms[0] = i + target
            terms[1] = terms[0] + target
            if (isPrime(terms[0]) && isPrime(terms[1]) && checkDigit(i, terms, digits)) {
                console.log(i.toString() + terms[0].toString() + terms[1].toString())
                return
            }
        }
    }
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

function checkDigit(value, terms, digits) {
    digits.fill(false)
    while (value) {
        digits[value % 10] = true
        value = Math.floor(value / 10)
    }

    for (let term of terms) {
        while (term) {
            if (!digits[term % 10]) {
                return false
            }
            term = Math.floor(term / 10)
        }
    }
    return true
}

module.exports = {
    Problem049 : Problem049
};
