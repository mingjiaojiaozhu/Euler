function Problem021() {
    let target = 10000
    let divisors = Array(target).fill(-1)
    for (let i = 2; i <= target; ++i) {
        getDivisorSummation(i, divisors, target)
    }
    for (let i = 1; i < target; ++i) {
        divisors[i] -= i + 1
    }

    let result = 0
    for (let i = 2; i <= target; ++i) {
        let divisor = divisors[i - 1]
        if (divisor > i && divisor <= target && divisors[divisor - 1] === i) {
            result += i + divisor
        }
    }
    console.log(result)
}

function getDivisorSummation(value, divisors, length) {
    if (-1 === divisors[value - 1]) {
        let index = value
        let count = 1
        while (index <= length) {
            divisors[index - 1] = (Math.pow(value, count + 1) - 1) / (value - 1)
            index *= value
            ++count
        }

        for (let i = Math.min(value - 1, Math.floor(length / value)); i >= 2; --i) {
            divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]
        }
    } else {
        for (let i = Math.min(value - 1, Math.floor(length / value)); i >= 2; --i) {
            if (isRelativelyPrime(value, i) && -1 === divisors[value * i - 1]) {
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]
            }
        }
    }
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
    Problem021 : Problem021
};
