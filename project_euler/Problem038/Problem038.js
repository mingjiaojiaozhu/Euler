function Problem038() {
    let digits = Array(9)
    for (let i = 9487; i >= 9234; --i) {
        digits.fill(false)
        if (isPandigital(i, digits) && isPandigital(i << 1, digits)) {
            console.log(i.toString() + (i << 1).toString())
            return
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
    Problem038 : Problem038
};
