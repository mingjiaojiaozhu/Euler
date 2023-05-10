function Problem039() {
    let target = 1000
    let result = 0
    let pivot = 0
    for (let i = target; i >= 2; i -= 2) {
        let count = 0
        for (let j = Math.floor(i / 3); j > 0; --j) {
            if (!((((i * i) >>> 1) - i * j) % (i - j)) && j < (((i * i) >>> 1) - i * j) / (i - j)) {
                ++count
            }
        }
        if (pivot < count) {
            pivot = count
            result = i
        }
    }
    console.log(result)
}

module.exports = {
    Problem039 : Problem039
};
