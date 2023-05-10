function Problem004() {
    let target = 100
    let result = 0
    for (let i = 999; i >= target; --i) {
        for (let j = i; j >= target; --j) {
            let value = i * j
            if (isPalindrome(value) && result < value) {
                result = value
                target = j
                break
            }
        }
    }
    console.log(result)
}

function isPalindrome(value) {
    let divisor = 1
    while (10 <= value / divisor) {
        divisor *= 10
    }

    while (value > 1) {
        let head = Math.floor(value / divisor)
        let tail = value % 10
        if (head !== tail) {
            return false
        }

        value = Math.floor(value % divisor / 10)
        divisor = Math.floor(divisor / 100)
    }
    return true
}

module.exports = {
    Problem004 : Problem004
};
