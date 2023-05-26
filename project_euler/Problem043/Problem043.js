function Problem043() {
    let elements = Array(10)
    elements[5] = 5
    let digits = Array(10).fill(false)
    digits[5] = true

    let start = 500
    while (start % 11) {
        ++start
    }

    let result = 0
    for (let i = start; i < 600; i += 11) {
        elements[6] = Math.floor((i % 100) / 10)
        elements[7] = i % 10
        if (5 !== elements[6] && 5 !== elements[7] && elements[6] !== elements[7]) {
            digits[elements[6]] = true
            digits[elements[7]] = true
            result += check13(elements, elements[6] * 100 + elements[7] * 10, digits)
            digits[elements[6]] = false
            digits[elements[7]] = false
        }
    }
    console.log(result)
}

function check13(elements, pivot, digits) {
    let result = 0
    for (let i = 0; i < 10; ++i) {
        if (!digits[i] && !((pivot + i) % 13)) {
            elements[8] = i
            digits[i] = true
            result += check17(elements, ((pivot + i) % 100) * 10, digits)
            digits[i] = false
        }
    }
    return result
}

function check17(elements, pivot, digits) {
    let result = 0
    for (let i = 0; i < 10; ++i) {
        if (!digits[i] && !((pivot + i) % 17)) {
            elements[9] = i
            digits[i] = true
            fill(elements, digits)
            result += permutation(elements, 0, 5)
            digits[i] = false
        }
    }
    return result
}

function fill(elements, digits) {
    let index = 4
    for (let i = digits.length - 1; i >= 0; --i) {
        if (!digits[i]) {
            elements[index] = i
            --index
        }
    }
}

function permutation(elements, index, length) {
    if (index === length) {
        if (!elements[0] || (elements[3] & 1) || (elements[2] + elements[3] + elements[4]) % 3 || (10 * elements[4] + elements[5] - (elements[6] << 1)) % 7) {
            return 0
        }

        let result = 0
        for (let element of elements) {
            result = result * 10 + element
        }
        return result
    }

    let result = permutation(elements, index + 1, length)
    for (let i = index + 1; i < length; ++i) {
        swap(elements, index, i)
        result += permutation(elements, index + 1, length)
        swap(elements, index, i)
    }
    return result
}

function swap(arrays, i, j) {
    arrays[i] ^= arrays[j]
    arrays[j] ^= arrays[i]
    arrays[i] ^= arrays[j]
}

module.exports = {
    Problem043 : Problem043
};
