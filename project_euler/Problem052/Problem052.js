function Problem052() {
    let target = 6
    let digits = Array(2)
    for (let i = 0; i < 2; ++i) {
        digits[i] = Array(10)
    }
    let index = 10
    while (true) {
        getDigits(index, digits[0])
        let isSame = true
        for (let i = target; i > 1; --i) {
            getDigits(index * i, digits[1])
            if (!checkDigits(digits)) {
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

function checkDigits(digits) {
    for (let i = 0; i < 10; ++i) {
        if (digits[0][i] !== digits[1][i]) {
            return false
        }
    }
    return true
}

module.exports = {
    Problem052 : Problem052
};
