function Problem031() {
    let target = 200
    let coins = [1, 2, 5, 10, 20, 50, 100, 200]
    let result = getWays(target, coins, coins.length - 1)
    console.log(result)
}

function getWays(target, coins, index) {
    if (!target || !index) {
        return 1
    }

    if (target < coins[index]) {
        return getWays(target, coins, index - 1)
    }
    return getWays(target, coins, index - 1) + getWays(target - coins[index], coins, index)
}

module.exports = {
    Problem031 : Problem031
};
