function Problem078() {
    let target = 1000000
    let ways = [setValue(1, 1), setValue(1, 1)]

    let length = 0
    while (target >= 1e5) {
        ++length
        target = Math.floor(target / 1e5)
    }

    let auxiliary = new Decimal(100, 0)
    let result = 2
    while (true) {
        let way = getWay(result, ways, auxiliary)
        if (isDivideExactly(way, length, target)) {
            console.log(result)
            return
        }
        ++result
    }
}

function setValue(value, length) {
    let decimal = new Decimal(length, 0)
    decimal.value[0] = value
    decimal.length = 1
    return decimal
}

function getWay(target, ways, auxiliary) {
    let delta = Math.floor(Math.sqrt(target * 24 + 1))
    let borders = [Math.floor((delta + 1) / 6) + 1, Math.floor((delta - 1) / 6) + 1]
    let factor = 1
    for (let i = 1; i < borders[1]; ++i) {
        getSummation(ways[target - (i * (i * 3 - 1) >>> 1)], factor, auxiliary)
        getSummation(ways[target - (i * (i * 3 + 1) >>> 1)], factor, auxiliary)
        factor *= -1
    }
    if (borders[0] !== borders[1]) {
        getSummation(ways[target - (borders[1] * (borders[1] * 3 - 1) >>> 1)], factor, auxiliary)
    }
    let result = new Decimal(auxiliary.length, 0)
    swapDecimal(auxiliary, result)
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

function swapDecimal(previous, current) {
    let length = Math.max(previous.length, current.length)
    for (let i = 0; i < length; ++i) {
        previous.value[i] ^= current.value[i]
        current.value[i] ^= previous.value[i]
        previous.value[i] ^= current.value[i]
    }
    previous.length ^= current.length
    current.length ^= previous.length
    previous.length ^= current.length
}

function Decimal(capacity, length) {
    this.value = Array(capacity).fill(0)
    this.length = length
}

module.exports = {
    Problem078 : Problem078
};
