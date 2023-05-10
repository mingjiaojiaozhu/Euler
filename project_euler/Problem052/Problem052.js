function Problem052() {
    let target = 6
    let pivots = Array(10)
    let digits = Array(10)
    let index = 10
    while (true) {
        getDigits(index, pivots)
        let isSame = true
        for (let i = target; i > 1; --i) {
            getDigits(index * i, digits)
            if (!checkDigits(pivots, digits)) {
                isSame = false
                break
            }
        }
        if (isSame) {
            console.log(index)
            return
        }
        ++index
    }
}

function getDigits(value, digits) {
    digits.fill(0)
    while (value) {
        ++digits[value % 10]
        value = Math.floor(value / 10)
    }
}

function checkDigits(pivots, digits) {
    for (let i = 0; i < 10; ++i) {
        if (pivots[i] !== digits[i]) {
            return false
        }
    }
    return true
}

module.exports = {
    Problem052 : Problem052
};
