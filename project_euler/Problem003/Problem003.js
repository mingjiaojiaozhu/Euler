function Problem003() {
    let target = 600851475143
    while (0 === (target & 1)) {
        target >>>= 1
    }
    if (1 === target) {
        target = 2
    }

    let factor = 3
    while (factor < target) {
        while (!(target % factor) && target !== factor) {
            target /= factor
        }
        factor += 2
    }
    console.log(target)
}

module.exports = {
    Problem003 : Problem003
};
