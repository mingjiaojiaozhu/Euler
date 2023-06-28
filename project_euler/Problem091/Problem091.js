function Problem091() {
    let target = 50
    let result = target * target * 3
    for (let i = 1; i < target; ++i) {
        for (let j = 1; j <= target; ++j) {
            let divisor = commonDivisor(i, j)
            result += Math.min(Math.floor((target - i) * divisor / j), Math.floor(j * divisor / i)) << 1
        }
    }
    console.log(result)
}

function commonDivisor(i, j) {
    while (i % j) {
        let auxiliary = i % j
        i = j
        j = auxiliary
    }
    return j
}

module.exports = {
    Problem091 : Problem091
};
