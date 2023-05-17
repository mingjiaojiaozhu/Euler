function Problem062() {
    let target = 5
    let cubes = new Map()
    let index = 5
    let pivot = 0
    while (true) {
        let value = Math.pow(index, 3)
        let summation = getSummation(value)
        let digit = Math.floor(Math.log10(value))
        if (pivot !== digit) {
            cubes.clear()
            pivot = digit
        } else {
            if (cubes.has(summation) && cubes.get(summation).length === target - 1) {
                console.log(cubes.get(summation)[0])
                return
            }
        }
        if (!cubes.has(summation)) {
            cubes.set(summation, [])
        }
        cubes.get(summation).push(value)
        ++index
    }
}

function getSummation(value) {
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
