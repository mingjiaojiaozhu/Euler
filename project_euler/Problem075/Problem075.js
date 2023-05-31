function Problem075() {
    let target = 1500000
    let border = Math.floor(Math.sqrt(target >>> 1))
    let perimeters = new Map()
    for (let i = 2; i <= border; ++i) {
        for (let j = 1; j < i; ++j) {
            if (0 !== ((i + j) & 1) && isRelativelyPrime(i, j)) {
                let pivot = i * (i + j) << 1
                let length = pivot;
                while (length < target) {
                    if (perimeters.has(length)) {
                        perimeters.set(length, perimeters.get(length) + 1)
                    } else {
                        perimeters.set(length, 1)
                    }
                    length += pivot;
                }
            }
        }
    }

    let result = 0
    for (let [, value] of perimeters) {
        if (1 === value) {
            ++result
        }
    }
    console.log(result)
}

function isRelativelyPrime(i, j) {
    while (i % j) {
        let auxiliary = i % j
        i = j
        j = auxiliary
    }
    return 1 === j
}

module.exports = {
    Problem075 : Problem075
};
