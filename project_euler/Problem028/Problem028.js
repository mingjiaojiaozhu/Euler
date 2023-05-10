function Problem028() {
    let target = 1001
    let steps = target >>> 1
    let result = (steps * steps * steps * 16 + steps * 26) / 3 + steps * steps * 10 + 1
    console.log(result)
}

module.exports = {
    Problem028 : Problem028
};
