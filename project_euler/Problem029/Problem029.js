function Problem029() {
    let start = 2
    let end = 100
    let terms = []
    for (let i = start; i <= end; ++i) {
        for (let j = start; j <= end; ++j) {
            terms.push(i * Math.log(j))
        }
    }

    terms.sort()

    let result = terms.length
    for (let i = result - 1; i >= 1; --i) {
        if (Math.abs(terms[i] - terms[i - 1]) < 0.00000001) {
            --result
        }
    }
    console.log(result)
}

module.exports = {
    Problem029 : Problem029
};
