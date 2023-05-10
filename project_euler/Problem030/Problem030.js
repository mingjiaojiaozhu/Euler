function Problem030() {
    let target = 5
    let powers = Array(10)
    for (let i = 0; i < 10; ++i) {
        powers[i] = Math.pow(i, target)
    }

    let result = 0
    for (let i = 6 * powers[9]; i >= 10; --i) {
        if (i === getPowerDigit(i, powers)) {
            result += i
        }
    }
    console.log(result)
}

function getPowerDigit(value, powers) {
    let result = 0
    while (value) {
        result += powers[value % 10]
        value = Math.floor(value / 10)
    }
    return result
}

module.exports = {
    Problem030 : Problem030
};
