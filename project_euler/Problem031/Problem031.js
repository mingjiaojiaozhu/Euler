function Problem031() {
    let target = 200
    let coins = [1, 2, 5, 10, 20, 50, 100, 200]
    let ways = Array(target + 1).fill(0)
    ways[0] = 1
    for (let coin of coins) {
        for (let i = coin; i <= target; ++i) {
            ways[i] += ways[i - coin]
        }
    }
    console.log(ways[target])
}

module.exports = {
    Problem031 : Problem031
};
