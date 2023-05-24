function Problem059() {
    let fileName = 'cipher.txt'
    let codes = Array(0)
    let counts = Array(3)
    for (let i = 0; i < 3; ++i) {
        counts[i] = new Map()
    }

    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    let index = 0
    while (line = handle.next()) {
        let code = Number(line.toString())
        codes.push(code)
        if (counts[index].has(code)) {
            counts[index].set(code, counts[index].get(code) + 1)
        } else {
            counts[index].set(code, 1)
        }
        ++index
        if (3 === index) {
            index = 0
        }
    }

    let keys = Array(3)
    for (let i = 0; i < 3; ++i) {
        let pivot = 0
        for (let [key, value] of counts[i]) {
            if (pivot < value) {
                pivot = value
                keys[i] = key
            }
        }
        keys[i] ^= ' '.charCodeAt(0)
    }

    let result = 0
    index = 0
    for (let code of codes) {
        result += code ^ keys[index]
        ++index
        if (3 === index) {
            index = 0
        }
    }
    console.log(result)
}

module.exports = {
    Problem059 : Problem059
};
