function Problem048() {
    let target = 1000
    let product = Array(2)
    let auxiliary = Array(2)
    let result = 0
    for (let i = Math.floor(target / 10) * 10 + 1; i <= target; ++i) {
        getPower(i, i, product, auxiliary)
        result += product[1] * 1e5 + product[0]
    }
    for (let i = Math.floor(target / 10) - 1; i >= 0; --i) {
        for (let j = 1; j < 10; ++j) {
            let value = i * 10 + j
            getPower(value, value, product, auxiliary)
            result += product[1] * 1e5 + product[0]
        }
    }
    console.log(result % 1e10)
}

function getPower(base, index, product, auxiliary) {
    if (1 === index) {
        product[0] = base
        product[1] = 0
        return
    }

    getPower(base, index >>> 1, product, auxiliary)
    getSquare(product, auxiliary)
    if (0 !== (index & 1)) {
        getProduct(base, product, auxiliary)
    }
}

function getSquare(product, auxiliary) {
    auxiliary[0] = product[0] * product[0]
    auxiliary[1] = product[0] * product[1] * 2
    carry(product, auxiliary)
}

function getProduct(value, product, auxiliary) {
    auxiliary[0] = product[0] * value
    auxiliary[1] = product[1] * value
    carry(product, auxiliary)
}

function carry(product, auxiliary) {
    if (auxiliary[0] >= 1e5) {
        auxiliary[1] += Math.floor(auxiliary[0] / 1e5)
        auxiliary[0] %= 1e5
    }
    auxiliary[1] %= 1e5
    product[0] = auxiliary[0]
    product[1] = auxiliary[1]
}

module.exports = {
    Problem048 : Problem048
};
