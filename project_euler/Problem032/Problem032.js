function Problem032() {
    let digits = Array(9)
    let products = new Set()
    for (let i = 1; i < 10; ++i) {
        for (let j = Math.floor(10000 / i); j >= 1234; --j) {
            getProducts(i, j, digits, products)
        }
    }

    for (let i = 10; i < 100; ++i) {
        for (let j = Math.floor(10000 / i); j >= 123; --j) {
            getProducts(i, j, digits, products)
        }
    }

    let result = 0
    for (let product of products) {
        result += product
    }
    console.log(result)
}

function getProducts(multiplicand, multiplier, digits, products) {
    digits.fill(false)
    if (isPandigital(multiplicand, digits) && isPandigital(multiplier, digits)) {
        let product = multiplicand * multiplier
        if (isPandigital(product, digits)) {
            products.add(product)
        }
    }
}

function isPandigital(value, digits) {
    while (value) {
        let index = value % 10 - 1
        if (index < 0 || digits[index]) {
            return false
        }
        digits[index] = true
        value = Math.floor(value / 10)
    }
    return true
}

module.exports = {
    Problem032 : Problem032
};
