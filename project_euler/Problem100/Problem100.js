function Problem100() {
    let target = 1000000000000
    let index = 1
    let result = 1
    while (index < target) {
        let auxiliary = index * 2 + result * 3 - 2
        index = index * 3 + result * 4 - 3
        result = auxiliary
    }
    console.log(result)
}

module.exports = {
    Problem100 : Problem100
};
