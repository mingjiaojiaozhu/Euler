function Problem041() {
    let elements = [7, 6, 5, 4, 3, 2, 1]
    let result = permutation(elements, 0, elements.length, 0)
    console.log(result)
}

function permutation(elements, index, length, pivot) {
    if (index === length) {
        let result = 0
        for (let element of elements) {
            result = result * 10 + element
        }
        if (isPrime(result)) {
            return Math.max(result, pivot)
        }
        return pivot
    }

    let result = permutation(elements, index + 1, length, pivot)
    for (let i = index + 1; i < length; ++i) {
        swap(elements, index, i)
        result = permutation(elements, index + 1, length, result)
        swap(elements, index, i)
    }
    return result
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

function swap(arrays, i, j) {
    arrays[i] ^= arrays[j]
    arrays[j] ^= arrays[i]
    arrays[i] ^= arrays[j]
}

module.exports = {
    Problem041 : Problem041
};
