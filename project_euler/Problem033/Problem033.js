function Problem033() {
    let numerator = 1
    let denominator = 1
    for (let i = 1; i < 10; ++i) {
        for (let j = i + 1; j < 10; ++j) {
            if (!((9 * i * j) % (10 * i - j)) && (9 * i * j) / (10 * i - j) < 10) {
                numerator *= i
                denominator *= j
            }
        }
    }
    console.log(denominator / commonDivisor(denominator, numerator))
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
    Problem033 : Problem033
};
