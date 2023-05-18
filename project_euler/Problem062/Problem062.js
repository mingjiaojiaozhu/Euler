function Problem062() {
    let target = 5
    let cubes = new Map()
    let index = 5
    let pivot = 0
    while (true) {
        let value = Math.pow(index, 3)
        let digits = getDigits(value)
        let count = Math.floor(Math.log10(value))
        if (pivot !== count) {
            cubes.clear()
            pivot = count
        } else {
            if (cubes.has(digits) && cubes.get(digits).length === target - 1) {
                console.log(cubes.get(digits)[0])
                return
            }
        }
        if (!cubes.has(digits)) {
            cubes.set(digits, [])
        }
        cubes.get(digits).push(value)
        ++index
    }
}

function getDigits(value) {
    let result = 0
    while (value) {
        result += Math.pow(10, value % 10)
        value = Math.floor(value / 10)
    }
    return result
}

module.exports = {
    Problem062 : Problem062
};
