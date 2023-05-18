function Problem064() {
    let target = 10000
    let result = 0
    for (let i = 1; i <= target; ++i) {
        if (0 !== (getPeriod(i) & 1)) {
            ++result
        }
    }
    console.log(result)
}

function getPeriod(value) {
    if (Math.abs(Math.floor(Math.sqrt(value) + 0.5) - Math.sqrt(value)) < 0.00000001) {
        return 0
    }

    let initial = Math.floor(Math.sqrt(value))
    let pivot = initial << 1
    let current = initial
    let offset = 0
    let factor = 1
    let count = 0
    while (current !== pivot) {
        offset = current * factor - offset
        factor = Math.floor((value - offset * offset) / factor)
        current = Math.floor((initial + offset) / factor)
        ++count
    }
    return count
}

module.exports = {
    Problem064 : Problem064
};
