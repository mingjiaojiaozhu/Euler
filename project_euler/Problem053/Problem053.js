function Problem053() {
    let target = 1000000
    let result = 0
    for (let i = 23; i <= 100; ++i) {
        result += i + 1 - (getIndex(i, target) << 1)
    }
    console.log(result)
}

function getIndex(value, target) {
    let start = 0
    let end = (value + 1) >>> 1
    while (start <= end) {
        let current = start + ((end - start) >>> 1)
        if (checkCombination(value, current, target)) {
            start = current + 1
        } else {
            end = current - 1
        }
    }
    return start
}

function checkCombination(value, count, target) {
    let result = 1
    for (let i = 0; i < count; ++i) {
        result = result * (value - i) / (i + 1)
        if (result > target) {
            return false
        }
    }
    return true
}

module.exports = {
    Problem053 : Problem053
};
