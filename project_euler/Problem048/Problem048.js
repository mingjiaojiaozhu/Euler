function Problem048() {
    let target = 1000
    let product = Array(2)
    let auxiliary = Array(2)
    let result = 0
    for (let i = 1; i <= target; ++i) {
        if (i % 10) {
            getPower(i, i, product, auxiliary);
            result += product[1] * 1e5 + product[0];
        }
    }
    console.log(result % 1e10)
}

function getPower(base, index, product, auxiliary) {
    if (1 === index) {
        product[0] = base
        product[1] = 0
        return;
    }

    getPower(base, index >> 1, product, auxiliary)
    getSquare(product, auxiliary)
    if (0 !== (index & 1)) {
        getProduct(base, product)
    }
}

function getSquare(product, auxiliary) {
    auxiliary[0] = product[0] * product[0]
    auxiliary[1] = product[0] * product[1] + product[1] * product[0]
    if (auxiliary[0] >= 1e5) {
        auxiliary[1] += Math.floor(auxiliary[0] / 1e5)
        auxiliary[0] %= 1e5
    }
    auxiliary[1] %= 1e5
    product[0] = auxiliary[0]
    product[1] = auxiliary[1]
}

function getProduct(value, product) {
    product[0] *= value
    product[1] *= value
    if (product[0] >= 1e5) {
        product[1] += Math.floor(product[0] / 1e5)
        product[0] %= 1e5
    }
    product[1] %= 1e5
}

module.exports = {
    Problem048 : Problem048
};
