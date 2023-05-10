function Problem025() {
    let target = 1000
    let result = Math.ceil((target - 1 + Math.log10(5) / 2) / Math.log10((1 + Math.sqrt(5)) / 2))
    console.log(result)
}

module.exports = {
    Problem025 : Problem025
};
