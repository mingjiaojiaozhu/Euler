function Problem088() {
    let target = 12000
    let length = Math.ceil(Math.log(target) / Math.log(2))
    let products = Array(target - 1).fill(Math.pow(2, length + 1))

    let digits = Array(length).fill(1)
    digits[0] = 2
    digits[1] = 2

    let pivot = target - length
    while (true) {
        let product = 1
        let summation = 0
        for (let value of digits) {
            product *= value
            summation += value
        }
        let difference = product - summation
        if (difference <= pivot) {
            let index = difference + length - 2
            if (index >= 0 && products[index] > product) {
                products[index] = product
            }
            ++digits[0]
        } else {
            if (!carry(digits, length)) {
                break
            }
        }
    }

    let result = 0
    let auxiliary = new Set()
    for (let value of products) {
        if (!auxiliary.has(value)) {
            result += value
            auxiliary.add(value)
        }
    }
    console.log(result)
}

function carry(digits, length) {
    for (let i = 1; i < length; ++i) {
        if (digits[i] !== digits[i - 1]) {
            ++digits[i]
            let value = digits[i]
            for (let j = 0; j < i; ++j) {
                digits[j] = value
            }
            return true
        }
    }
    return false
}

module.exports = {
    Problem088 : Problem088
};
