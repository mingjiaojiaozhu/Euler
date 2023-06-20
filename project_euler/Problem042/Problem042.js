function Problem042() {
    let fileName = 'words.txt'
    let result = 0
    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    while (line = handle.next()) {
        let value = 0
        for (let letter of line.toString()) {
            value += letter.charCodeAt(0) - 'A'.charCodeAt(0) + 1
        }
        let auxiliary = Math.sqrt((value << 3) + 1)
        if (Math.abs(Math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && (Math.floor(auxiliary) & 1)) {
            ++result
        }
    }
    console.log(result)
}

module.exports = {
    Problem042 : Problem042
};
