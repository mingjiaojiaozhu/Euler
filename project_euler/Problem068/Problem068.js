function Problem068() {
    let target = 10
    let ring = []
    let border = target >>> 1
    let start = border + 1
    ring.push(start)
    ring.push(border)
    let summation = ((target * (target + 1) >>> 1) + (border * (border + 1) >>> 1)) / border
    let pivot = summation - border - start
    ring.push(pivot)
    for (let i = target; i > start; --i) {
        ring.push(i)
        ring.push(pivot)
        pivot = summation - pivot - i
        ring.push(pivot)
    }

    let result = 0
    for (let value of ring) {
        if (value >= 10) {
            result = result * 100 + value
        } else {
            result = result * 10 + value
        }
    }
    console.log(result)
}

module.exports = {
    Problem068 : Problem068
};
