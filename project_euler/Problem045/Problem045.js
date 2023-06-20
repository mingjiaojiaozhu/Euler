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
    let auxiliary = Math.sqrt(value * 24 + 1)
    return Math.abs(Math.floor(auxiliary + 0.5) - auxiliary) < 0.00000001 && !((Math.floor(auxiliary) + 1) % 6)
}

module.exports = {
    Problem045 : Problem045
};
