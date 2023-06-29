function Problem097() {
    let target = 7830457
    let factor = 28433
    let product = Array(2)
    let auxiliary = Array(2)
    getPower(target, product, auxiliary)
    getProduct(factor, 1, product, auxiliary)

    let result = product[1] * 1e5 + product[0]
    console.log(result)
}

function getPower(value, product, auxiliary) {
    if (value < 8) {
        product[0] = Math.pow(2, value)
        product[1] = 0
        return
    }

    getPower(value >>> 1, product, auxiliary)
    getSquare(product, auxiliary)
    if (0 !== (value & 1)) {
        getDouble(product)
    }
}

function getProduct(factor, value, product, auxiliary) {
    auxiliary[0] = product[0] * factor + value
    auxiliary[1] = product[1] * factor
    carry(product, auxiliary)
}

function getSquare(product, auxiliary) {
    auxiliary[0] = product[0] * product[0]
    auxiliary[1] = product[0] * product[1] * 2
    carry(product, auxiliary)
}

function getDouble(product) {
    product[0] <<= 1
    product[1] <<= 1
    if (product[0] >= 1e5) {
        product[1] += Math.floor(product[0] / 1e5)
        product[0] %= 1e5
    }
    product[1] %= 1e5
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
    Problem097 : Problem097
};
