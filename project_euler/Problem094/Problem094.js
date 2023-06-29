function Problem094() {
    let target = 1000000000
    let index = [2, 1]
    let result = 0
    while (true) {
        let auxiliary = (index[0] << 1) + index[1] * 3
        index[1] = index[0] + (index[1] << 1)
        index[0] = auxiliary

        let value = getTriangle(index, -1, target)
        if (-1 === value) {
            break
        }
        result += value

        value = getTriangle(index, 1, target)
        if (-1 === value) {
            break
        }
        result += value
    }
    console.log(result)
}

function getTriangle(index, offset, target) {
    let perimeter = (index[0] + offset) << 1
    if (perimeter >= target) {
        return -1
    }

    let length = ((index[0] << 1) + offset) / 3
    if (Math.abs(Math.floor(length + 0.5) - length) > 0.00000001) {
        return 0
    }
    let area = (length + offset) * index[1] / 2
    if (Math.abs(Math.floor(area + 0.5) - area) > 0.00000001) {
        return 0
    }
    return perimeter
}

module.exports = {
    Problem094 : Problem094
};
