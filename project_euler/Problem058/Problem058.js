function Problem058() {
    let target = 0.1
    let index = 3
    let count = 0
    while (true) {
        let value = index * index
        for (let i = 0; i < 3; ++i) {
            value -= index - 1
            if (isPrime(value)) {
                ++count
            }
        }

        if (count < ((index << 1) - 1) * target) {
            console.log(index)
            return
        }
        index += 2
    }
}

function isPrime(value) {
    if (0 === (value & 1)) {
        return 2 === value
    }

    let border = Math.floor(Math.sqrt(value))
    for (let i = 3; i <= border; i += 2) {
        if (!(value % i)) {
            return false
        }
    }
    return 1 !== value
}

module.exports = {
    Problem058 : Problem058
};
