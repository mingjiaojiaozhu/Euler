function Problem082() {
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

    let ways = Array(border)
    for (let i = 0; i < border; ++i) {
        ways[i] = target[i][border - 1]
    }
    for (let i = border - 2; i >= 0; --i) {
        ways[0] += target[0][i]
        for (let j = 1; j < border; ++j) {
            if (ways[j] > ways[j - 1]) {
                ways[j] = ways[j - 1] + target[j][i]
            } else {
                ways[j] += target[j][i]
            }
        }
        for (let j = border - 2; j >= 0; --j) {
            if (ways[j] > ways[j + 1] + target[j][i]) {
                ways[j] = ways[j + 1] + target[j][i]
            }
        }
    }

    let result = ways[0]
    for (let value of ways) {
        if (result > value) {
            result = value
        }
    }
    console.log(result)
}

module.exports = {
    Problem082 : Problem082
};
