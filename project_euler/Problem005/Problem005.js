function Problem005() {
    let target = 20
    let powers = Array(target).fill(0)
    for (let i = 2; i <= target; ++i) {
        factorize(i, powers)
    }

    let result = 1
    for (let [i, power] of powers.entries()) {
        for (let j = 0; j < power; ++j) {
            result *= i + 1
        }
    }
    console.log(result)
}

function factorize(value, powers) {
    let power = 0
    while (0 === (value & 1)) {
        value >>>= 1
        ++power
    }
    if (powers[1] < power) {
        powers[1] = power
    }

    let factor = 3
    while (factor <= value) {
        power = 0
        while (!(value % factor)) {
            value /= factor
            ++power
        }
        if (powers[factor - 1] < power) {
            powers[factor - 1] = power
        }
        factor += 2
    }
}

module.exports = {
    Problem005 : Problem005
};
