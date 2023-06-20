function Problem085() {
    let target = 2000000
    let border = Math.floor(Math.sqrt(1 + 8 * Math.sqrt(target)) - 1) >>> 1
    let result = 0
    let pivot = target
    for (let i = 1; i <= border; ++i) {
        let length = Math.floor(Math.sqrt(1 + (target << 4) / i / (i + 1)) - 1) >>> 1
        let value = Math.min(Math.abs(getCount(length, i) - target), Math.abs(getCount(length + 1, i) - target))
        if (pivot > value) {
            result = length * i
            pivot = value
        }
    }
    console.log(result)
}

function getCount(length, width) {
    return length * (length + 1) * width * (width + 1) >>> 2
}

module.exports = {
    Problem085 : Problem085
};
