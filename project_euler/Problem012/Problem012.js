function Problem012() {
    let target = 500
    let previous = getDivisors(1)
    let index = 1
    while (true) {
        let current = getDivisors(index + 1)
        let value = previous * current
        if (value > target) {
            break
        }

        ++index
        previous = current
    }
    let result = index * (index + 1) >>> 1
    console.log(result)
}

function getDivisors(value) {
    let result = 1
    if (0 === (value & 1)) {
        let power = 0
        while (0 === (value & 1)) {
            value >>>= 1
            ++power
        }
        result *= power
    }

    let factor = 3
    while (factor <= value) {
        let power = 0
        while (!(value % factor)) {
            value /= factor
            ++power
        }
        result *= power + 1
        factor += 2
    }
    return result
}

module.exports = {
    Problem012 : Problem012
};
