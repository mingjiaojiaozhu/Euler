function Problem086() {
    let target = 1000000
    let count = 0
    let result = 1
    while (count < target) {
        ++result
        for (let i = 3; i < result; ++i) {
            let root = Math.sqrt(result * result + i * i)
            if (Math.abs(Math.floor(root + 0.5) - root) < 0.00000001) {
                count += i >>> 1
            }
        }
        for (let i = (result << 1) - 1; i >= result; --i) {
            let root = Math.sqrt(result * result + i * i)
            if (Math.abs(Math.floor(root + 0.5) - root) < 0.00000001) {
                count += result - ((i + 1) >>> 1) + 1
            }
        }
    }
    console.log(result)
}

module.exports = {
    Problem086 : Problem086
};
