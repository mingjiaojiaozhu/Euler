function Problem001() {
    let target = 1000
    let result = getSummation(target, 3) + getSummation(target, 5) - getSummation(target, 3 * 5)
    console.log(result)
}

function getSummation(border, factor) {
    let count = Math.floor((border - 1) / factor)
    return factor * count * (count + 1) >>> 1
}

module.exports = {
    Problem001 : Problem001
};
