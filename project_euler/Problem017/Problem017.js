function Problem017() {
    let lettersBelow10 = [3, 3, 5, 4, 4, 3, 5, 5, 4]
    let letters10To19 = [3, 6, 6, 8, 8, 7, 7, 9, 8, 8]
    let lettersWholeTen = [6, 6, 5, 5, 5, 7, 6, 6]
    let letter100 = 7
    let letterAnd = 3
    let letter1000 = 8

    let countBelow10 = 0
    for (let letter of lettersBelow10) {
        countBelow10 += letter
    }

    let countBelow100 = countBelow10 * 9
    for (let letter of letters10To19) {
        countBelow100 += letter
    }
    for (let letter of lettersWholeTen) {
        countBelow100 += letter * 10
    }

    let result = countBelow100 * 10 + countBelow10 * 100 + letter100 * 100 * 9 + letterAnd * 99 * 9 + lettersBelow10[0] + letter1000
    console.log(result)
}

module.exports = {
    Problem017 : Problem017
};
