function Problem022() {
    let fileName = 'names.txt'
    let names = []

    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    while (line = handle.next()) {
        names.push(line.toString())
    }

    names.sort(function(i, j) {return i.localeCompare(j)})

    let result = 0
    for (let [i, name] of names.entries()) {
        let score = 0
        for (let letter of name) {
            score += letter.charCodeAt(0) - 'A'.charCodeAt(0) + 1
        }
        result += score * (i + 1)
    }
    console.log(result)
}

module.exports = {
    Problem022 : Problem022
};
