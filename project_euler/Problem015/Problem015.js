function Problem015() {
    let target = 20
    let border = target << 1
    let result = 1
    for (let i = border - 1; i > target; i -= 2) {
        result = Math.floor(result * 2 * i / ((border - i + 1) >>> 1))
    }
    console.log(result)
}

module.exports = {
    Problem015 : Problem015
};
