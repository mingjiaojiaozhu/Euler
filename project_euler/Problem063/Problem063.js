function Problem063() {
    let result = 0
    for (let i = 1; i < 10; ++i) {
        result += Math.floor(1 / (1 - Math.log10(i)))
    }
    console.log(result)
}

module.exports = {
    Problem063 : Problem063
};
