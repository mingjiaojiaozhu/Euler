function Problem047() {
    let target = 4
    let length = 200000
    let factors = Array(length).fill(-1)

    let count = 0
    for (let i = 2; i <= length; ++i) {
        if (target === getFactors(i, factors, length)) {
            ++count
            if (target === count) {
                console.log(i - 3)
                return
            }
        } else {
            count = 0
        }
    }
}

function getFactors(value, factors, length) {
    if (-1 === factors[value - 1]) {
        let index = value
        while (index <= length) {
            factors[index - 1] = 1
            index *= value
        }

        for (let i = Math.min(value - 1, Math.floor(length / value)); i >= 2; --i) {
            factors[value * i - 1] = factors[value - 1] + factors[i - 1]
        }
    } else {
        for (let i = Math.min(value - 1, Math.floor(length / value)); i >= 2; --i) {
            if (isRelativelyPrime(value, i) && -1 === factors[value * i - 1]) {
                factors[value * i - 1] = factors[value - 1] + factors[i - 1]
            }
        }
    }
    return factors[value - 1]
}

function isRelativelyPrime(i, j) {
    while (i % j) {
        let auxiliary = i % j
        i = j
        j = auxiliary
    }
    return 1 === j
}

module.exports = {
    Problem047 : Problem047
};
