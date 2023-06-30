function Problem099() {
    let fileName = 'base_exp.txt'
    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    let index = 1
    let pivot = 0
    let result = 0
    while (line = handle.next()) {
        let elements = line.toString().split(' ')
        let value = Math.log(Number(elements[0])) * Number(elements[1])
        if (pivot < value) {
            pivot = value
            result = index
        }
        ++index
    }
    console.log(result)
}

module.exports = {
    Problem099 : Problem099
};
