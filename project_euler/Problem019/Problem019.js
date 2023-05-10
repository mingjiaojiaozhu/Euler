function Problem019() {
    let start = 1900
    let end = 2000
    let days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    let length = days.length

    let week = 1
    for (let day of days) {
        week += day
    }
    if (!(start % 4) && (start % 100 || !(start % 400))) {
        ++week
    }
    week %= 7

    let result = 0
    for (let i = start + 1; i <= end; ++i) {
        for (let j = 0; j < length; ++j) {
            if (!week) {
                ++result
            }

            week += days[j]
            if (1 === j && (!(start % 4) && (start % 100 || !(start % 400)))) {
                ++week
            }
            week %= 7
        }
    }
    console.log(result)
}

module.exports = {
    Problem019 : Problem019
};
