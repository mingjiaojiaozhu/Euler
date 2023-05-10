function Problem044() {
    let pentagons = []
    let index = 1
    while (true) {
        let current = index * (3 * index - 1) >> 1
        for (let pentagon of pentagons) {
            if (isPentagon(current + pentagon) && isPentagon(current - pentagon)) {
                console.log(current - pentagon)
                return
            }
        }
        pentagons.push(current)
        ++index
    }
}

function isPentagon(value) {
    let delta = value * 24 + 1
    return Math.abs(Math.floor(Math.sqrt(delta) + 0.5) - Math.sqrt(delta)) < 0.00000001 && !((Math.floor(Math.sqrt(delta)) + 1) % 6)
}

module.exports = {
    Problem044 : Problem044
};
