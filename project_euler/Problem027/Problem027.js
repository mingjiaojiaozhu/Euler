function Problem027() {
    let target = 1000
    let border = -1 * (target - 1)
    let result = 0
    let pivot = 0
    for (let i = 3; i < target; i += 2) {
        if (!isPrime(i)) {
            continue
        }

        for (let j = border; j < target; j += 2) {
            let count = 1
            while (isPrime(count * count + count * j + i)) {
                ++count
            }
            if (pivot < count) {
                pivot = count
                result = i * j
            }
        }
    }
    console.log(result)
}

function isPrime(value) {
    if (value <= 0) {
        return false
    }
    if (1 !== value % 6 && 5 !== value % 6) {
        return 2 === value || 3 === value
    }

    let border = Math.floor(Math.sqrt(value))
    for (let i = 5; i <= border; i += 6) {
        if (!(value % i) || !(value % (i + 2))) {
            return false
        }
    }
    return 1 !== value
}

module.exports = {
    Problem027 : Problem027
};
