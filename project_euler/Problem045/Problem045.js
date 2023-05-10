function Problem045() {
    let index = 144
    while (true) {
        let hexagon = index * ((index << 1) - 1)
        if (isPentagon(hexagon)) {
            console.log(hexagon)
            return
        }
        ++index
    }
}

function isPentagon(value) {
    let delta = value * 24 + 1
    return Math.abs(Math.floor(Math.sqrt(delta) + 0.5) - Math.sqrt(delta)) < 0.00000001 && !((Math.floor(Math.sqrt(delta)) + 1) % 6)
}

module.exports = {
    Problem045 : Problem045
};
