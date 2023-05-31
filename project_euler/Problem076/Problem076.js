function Problem076() {
    let target = 100
    let ways = Array(target + 1).fill(0)
    ways[0] = 1
    for (let i = 1; i < target; ++i) {
        for (let j = i; j <= target; ++j) {
            ways[j] += ways[j - i]
        }
    }
    console.log(ways[target])
}

module.exports = {
    Problem076 : Problem076
};
