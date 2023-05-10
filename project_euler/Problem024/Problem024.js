function Problem024() {
    let target = 1000000
    let elements = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    permutation(target - 1, elements, elements.length, 0)

    let result = 0
    for (let element of elements) {
        result = result * 10 + element
    }
    console.log(result)
}

function permutation(sequence, elements, length, start) {
    if (1 === length - start) {
        return
    }

    let count = getFactorial(length - start - 1)
    let index = Math.floor(sequence / count) + start
    if (index !== start) {
        let auxiliary = elements[index]
        for (let i = index; i > start; --i) {
            elements[i] = elements[i - 1]
        }
        elements[start] = auxiliary
    }
    ++start
    permutation(sequence % count, elements, length, start)
}

function getFactorial(value) {
    let result = 1
    for (let i = 2; i <= value; ++i) {
        result *= i
    }
    return result
}

module.exports = {
    Problem024 : Problem024
};
