function Problem079() {
    let fileName = 'keylog.txt'
    let length = 10
    let elements = Array(length)
    for (let i = 0; i < length; ++i) {
        elements[i] = Array(length).fill(0)
    }
    let visited = Array(length).fill(true)

    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    while (line = handle.next()) {
        createElements(Number(line.toString()), elements, visited)
    }

    let digits = []
    for (let i = 0; i < length; ++i) {
        if (!visited[i]) {
            search(elements, i, digits, visited, length)
        }
    }

    let result = 0
    for (let i = digits.length - 1; i >= 0; --i) {
        result = result * 10 + digits[i]
    }
    console.log(result)
}

function createElements(value, elements, visited) {
    let tail = value % 10
    visited[tail] = false
    while (value >= 10) {
        value = Math.floor(value / 10)
        let head = value % 10
        elements[head][tail] = 1
        tail = head
        visited[tail] = false
    }
}

function search(elements, start, digits, visited, length) {
    visited[start] = true
    let element = elements[start]
    for (let i = 0; i < length; ++i) {
        if (element[i] && !visited[i]) {
            search(elements, i, digits, visited, length)
        }
    }
    digits.push(start)
}

module.exports = {
    Problem079 : Problem079
};
