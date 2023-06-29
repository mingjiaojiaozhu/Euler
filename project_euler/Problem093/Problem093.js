function Problem093() {
    let signs = ['+', '-', '*', '/']
    let operations = []
    getOperations(signs, operations)

    let elements = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    let auxiliary = Array(4)
    let result = new Arithmetic(0, 0)
    let calculations = new Set()
    combination(elements, 0, 4, auxiliary, 0, operations, result, calculations)
    console.log(result.value)
}

function getOperations(signs, operations) {
    let auxiliary = Array(3)
    search(signs, 3, operations, auxiliary, 0)
}

function combination(elements, index, count, auxiliary, size, operations, pivot, calculations) {
    if (count === size) {
        calculations.clear()
        permutation(auxiliary, 0, count, operations, calculations)
        let border = 1
        while (calculations.has(border)) {
            ++border
        }
        --border
        if (pivot.border < border) {
            pivot.border = border
            pivot.value = 0
            for (let value of auxiliary) {
                pivot.value = pivot.value * 10 + value
            }
        }
        return
    }

    for (let [i, value] of elements.slice(index).entries()) {
        auxiliary[size] = value
        ++size
        combination(elements, index + i + 1, count, auxiliary, size, operations, pivot, calculations)
        --size
    }
}

function search(signs, count, operations, auxiliary, size) {
    if (count === size) {
        operations.push(auxiliary.slice())
        return
    }

    for (let value of signs) {
        auxiliary[size] = value
        ++size
        search(signs, count, operations, auxiliary, size)
        --size
    }
}

function permutation(elements, index, length, operations, calculations) {
    if (index === length) {
        for (let operation of operations) {
            addCalculations(calculate(operation[2], calculate(operation[1], calculate(operation[0], elements[0], elements[1]), elements[2]), elements[3]), calculations)
            addCalculations(calculate(operation[1], calculate(operation[0], elements[0], elements[1]), calculate(operation[2], elements[2], elements[3])), calculations)
            addCalculations(calculate(operation[2], calculate(operation[0], elements[0], calculate(operation[1], elements[1], elements[2])), elements[3]), calculations)
            addCalculations(calculate(operation[0], elements[0], calculate(operation[2], calculate(operation[1], elements[1], elements[2]), elements[3])), calculations)
            addCalculations(calculate(operation[0], elements[0], calculate(operation[1], elements[1], calculate(operation[2], elements[2], elements[3]))), calculations)
        }
        return
    }

    permutation(elements, index + 1, length, operations, calculations)
    for (let i = index + 1; i < length; ++i) {
        swap(elements, index, i)
        permutation(elements, index + 1, length, operations, calculations)
        swap(elements, index, i)
    }
}

function addCalculations(value, calculations) {
    if (value > 0 && Math.abs(Math.floor(value + 0.5) - value) < 0.00000001) {
        calculations.add(Math.floor(value + 0.5))
    }
}

function calculate(sign, i, j) {
    if ('+' === sign) {
        return i + j
    }
    if ('-' === sign) {
        return i - j
    }
    if ('*' === sign) {
        return i * j
    }
    if (Math.abs(j) < 0.00000001) {
        return -1
    }
    return i / j
}

function swap(arrays, i, j) {
    arrays[i] ^= arrays[j]
    arrays[j] ^= arrays[i]
    arrays[i] ^= arrays[j]
}

function Arithmetic(border, value) {
    this.border = border
    this.value = value
}

module.exports = {
    Problem093 : Problem093
};
