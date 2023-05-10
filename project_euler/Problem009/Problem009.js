function Problem009() {
    let target = 1000
    for (let i = Math.floor(target / 3); i > 0; --i) {
        for (let j = target >>> 1; j > i; --j) {
            let remainder = target - i - j
            if (i * i + j * j === remainder * remainder) {
                console.log(i * j * remainder)
                return
            }
        }
    }
}

module.exports = {
    Problem009 : Problem009
};
