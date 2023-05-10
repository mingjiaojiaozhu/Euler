function Problem034() {
    let factorials = Array(10000)
    factorials[0] = 1
    let auxiliary = Array(10000)
    auxiliary[0] = 4
    for (let i = 1; i < 10; ++i) {
        factorials[i] = factorials[i - 1] * i
        auxiliary[i] = factorials[i] + 3
    }

    let result = 0
    for (let i = 10; i < 10000; ++i) {
        factorials[i] = factorials[Math.floor(i / 10)] + factorials[i % 10]
        if (i === factorials[i]) {
            result += i
        }
    }

    for (let i = 10; i < 100; ++i) {
        auxiliary[i] = factorials[i] + 2
    }
    for (let i = 100; i < 1000; ++i) {
        auxiliary[i] = factorials[i] + 1
    }
    for (let i = 1000; i < 10000; ++i) {
        auxiliary[i] = factorials[i]
    }

    for (let i = 6 * factorials[9] + 2; i >= 10000; --i) {
        if (i === getFactorialDigit(i, factorials, auxiliary)) {
            result += i
        }
    }
    console.log(result)
}

function getFactorialDigit(value, factorials, auxiliary) {
    let result = 0
    while (value >= 10000) {
        result += auxiliary[value % 10000]
        value = Math.floor(value / 10000)
    }
    result += factorials[value]
    return result
}

module.exports = {
    Problem034 : Problem034
};
