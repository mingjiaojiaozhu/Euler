function Problem081() {
    let fileName = 'matrix.txt'
    let border = 80
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

    for (let i = 1; i < border; ++i) {
        target[0][i] += target[0][i - 1]
        target[i][0] += target[i - 1][0]
    }
    for (let i = 1; i < border; ++i) {
        for (let j = 1; j < border; ++j) {
            target[i][j] += Math.min(target[i - 1][j], target[i][j - 1])
        }
    }
    console.log(target[border - 1][border - 1])
}

module.exports = {
    Problem081 : Problem081
};
