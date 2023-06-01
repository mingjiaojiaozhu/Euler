function Problem078() {
    let target = 1000000
    let ways = [setValue(1), setValue(1)]

    let length = 0
    while (target >= 1e5) {
        ++length
        target = Math.floor(target / 1e5)
    }

    let result = 2
    while (true) {
        let way = getWay(result, ways)
        if (isDivideExactly(way, length, target)) {
            console.log(result)
            return
        }
        ++result
    }
}

function setValue(value) {
    let decimal = new Decimal(100, 0)
    decimal.value[0] = value
    decimal.length = 1
    return decimal
}

function getWay(target, ways) {
    let result = setValue(0)
    let factor = 1
    for (let i = 1; i <= target; ++i) {
        if (!addDecimal(target - (i * (i * 3 - 1) >> 1), ways, factor, result) || !addDecimal(target - (i * (i * 3 + 1) >> 1), ways, factor, result)) {
            break
        }
        factor *= -1
    }
    ways.push(result)
    return result
}

function isDivideExactly(way, length, target) {
    if (way.length <= length) {
        return false
    }

    for (let i = 0; i < length; ++i) {
        if (way.value[i]) {
            return false
        }
    }
    return 0 === way.value[length] % target
}

function addDecimal(index, ways, factor, result) {
    if (index < 0) {
        return false
    }
    getSummation(ways[index], factor, result)
    return true
}

function getSummation(decimal, factor, summation) {
    for (let i = 0; i < decimal.length; ++i) {
        summation.value[i] += decimal.value[i] * factor
    }

    if (factor > 0) {
        for (let i = 0; i < summation.length; ++i) {
            if (summation.value[i] >= 1e5) {
                summation.value[i + 1] += Math.floor(summation.value[i] / 1e5)
                summation.value[i] %= 1e5
            }
        }
        if (summation.value[summation.length]) {
            ++summation.length
        }
    } else {
        for (let i = 0; i < summation.length; ++i) {
            if (summation.value[i] < 0) {
                --summation.value[i + 1]
                summation.value[i] += 1e5
            }
        }
        while (!summation.value[summation.length - 1]) {
            --summation.length
        }
    }
}

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem078 : Problem078
};
