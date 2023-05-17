function Problem067() {
    let fileName = 'triangle.txt'
    let border = 100
    let target = Array(border)
    for (let i = 0; i < border; ++i) {
        target[i] = Array(border)
    }

    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    let index = 0
    while (line = handle.next()) {
        let elements = line.toString().split(' ')
        for (let [i, element] of elements.entries()) {
            target[index][i] = Number(element)
        }
        ++index
    }

    for (let i = border - 1; i > 0; --i) {
        for (let j = i - 1; j >= 0; --j) {
            target[i - 1][j] += Math.max(target[i][j], target[i][j + 1])
        }
    }
    console.log(target[0][0])
}

module.exports = {
    Problem067 : Problem067
};
