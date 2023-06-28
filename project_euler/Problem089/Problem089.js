function Problem089() {
    let fileName = 'roman.txt'
    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    let result = 0
    while (line = handle.next()) {
        let previous = ' '
        let pivot = ' '
        let count = 1
        for (let value of line.toString()) {
            if (pivot === value) {
                ++count
            } else {
                previous = pivot
                pivot = value
                count = 1
            }

            if (count >= 4) {
                if (('I' === pivot && 'V' === previous) || ('X' === pivot && 'L' === previous) || ('C' === pivot && 'D' === previous)) {
                    result += 3
                } else if ('M' !== pivot) {
                    result += 2
                }
            }
        }
    }
    console.log(result)
}

module.exports = {
    Problem089 : Problem089
};
