function Problem090() {
    let elements = [0, 1, 2, 3, 4, 5, 6, 7, 8, 6]
    let ways = []
    let auxiliary = Array(6)
    combination(elements, 0, 6, elements.length, ways, auxiliary, 0)

    let squares = []
    for (let i = 1; i < 10; ++i) {
        squares.push(reverse9To6(i * i))
    }

    let result = 0
    let arrangements = new Set()
    for (let [i] of ways.entries()) {
        for (let j = 0; j <= i; ++j) {
            if (checkDigits(ways, i, j, squares, arrangements)) {
                ++result
            }
        }
    }
    console.log(result)
}

function combination(elements, start, count, length, ways, auxiliary, size) {
    if (count === size) {
        ways.push(auxiliary.slice())
        return
    }

    for (let i = start; i < length; ++i) {
        auxiliary[size] = elements[i]
        ++size
        combination(elements, i + 1, count, length, ways, auxiliary, size)
        --size
    }
}

function reverse9To6(value) {
    if (9 === Math.floor(value / 10)) {
        value -= 30
    }
    if (9 === value % 10) {
        value -= 3
    }
    return value
}

function checkDigits(ways, start, end, squares, arrangements) {
    arrangements.clear()
    for (let pivot of ways[start]) {
        for (let value of ways[end]) {
            arrangements.add(pivot * 10 + value)
            arrangements.add(value * 10 + pivot)
        }
    }

    for (let value of squares) {
        if (!arrangements.has(value)) {
            return false
        }
    }
    return true
}

module.exports = {
    Problem090 : Problem090
};
