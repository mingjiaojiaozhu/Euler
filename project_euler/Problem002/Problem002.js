function Problem002() {
    let target = 4000000
    let previous = [2, 8]
    let result = previous[0] + previous[1]
    while (true) {
        let current = previous[0] + (previous[1] << 2)
        if (current > target) {
            break
        }

        result += current
        previous[0] = previous[1]
        previous[1] = current
    }
    console.log(result)
}

module.exports = {
    Problem002 : Problem002
};
