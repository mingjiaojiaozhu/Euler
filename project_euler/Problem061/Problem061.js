function Problem061() {
    let target = 6
    let polygonals = []
    addTriangle(polygonals)
    addSquare(polygonals)
    addPentagonal(polygonals)
    addHexagonal(polygonals)
    addHeptagonal(polygonals)
    addOctagonal(polygonals)

    let length = polygonals.length
    let edges = Array(length)
    for (let i = 0; i < length; ++i) {
        edges[i] = Array(length).fill(0)
    }
    for (let i = 0; i < length; ++i) {
        let pivot = polygonals[i]
        for (let j = i + 1; j < length; ++j) {
            let polygonal = polygonals[j]
            if (pivot.step !== polygonal.step) {
                if (pivot.tail === polygonal.head) {
                    edges[i][j] = 1
                }
                if (polygonal.tail === pivot.head) {
                    edges[j][i] = 1
                }
            }
        }
    }

    let indexes = []
    let steps = Array(target).fill(false)
    let pivot = polygonals[0].step
    steps[pivot] = true
    for (let i = 0; i < length; ++i) {
        indexes.push(i)
        let step = polygonals[i].step
        if (step !== pivot) {
            return
        }
        search(polygonals, edges, i, indexes, steps, target)
        indexes.pop()
    }
}

function addTriangle(polygonals) {
    let index = Math.ceil((Math.sqrt(8001) - 1) / 2)
    while (true) {
        let value = index * (index + 1) >>> 1
        if (value >= 10000) {
            return
        }
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 0))
        }
        ++index
    }
}

function addSquare(polygonals) {
    let index = Math.ceil(Math.sqrt(1000))
    while (true) {
        let value = index * index
        if (value >= 10000) {
            return
        }
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 1))
        }
        ++index
    }
}

function addPentagonal(polygonals) {
    let index = Math.ceil((Math.sqrt(24001) + 1) / 6)
    while (true) {
        let value = index * (3 * index - 1) >>> 1
        if (value >= 10000) {
            return
        }
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 2))
        }
        ++index
    }
}

function addHexagonal(polygonals) {
    let index = Math.ceil((Math.sqrt(8001) + 1) / 4)
    while (true) {
        let value = index * ((index << 1) - 1)
        if (value >= 10000) {
            return
        }
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 3))
        }
        ++index
    }
}

function addHeptagonal(polygonals) {
    let index = Math.ceil((Math.sqrt(40009) + 3) / 10)
    while (true) {
        let value = index * (5 * index - 3) >>> 1
        if (value >= 10000) {
            return
        }
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 4))
        }
        ++index
    }
}

function addOctagonal(polygonals) {
    let index = Math.ceil((Math.sqrt(12002) + 2) / 6)
    while (true) {
        let value = index * (3 * index - 2)
        if (value >= 10000) {
            return
        }
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 5))
        }
        ++index
    }
}

function search(polygonals, edges, start, indexes, steps, target) {
    if (indexes.length === target) {
        if (polygonals[indexes[0]].head === polygonals[indexes[target - 1]].tail) {
            let result = 0
            for (let index of indexes) {
                let polygonal = polygonals[index]
                result += polygonal.head * 100 + polygonal.tail
            }
            console.log(result)
        }
        return
    }

    for (let i = polygonals.length - 1; i >= 0; --i) {
        if (edges[start][i]) {
            let step = polygonals[i].step
            if (!steps[step]) {
                indexes.push(i)
                steps[step] = true
                search(polygonals, edges, i, indexes, steps, target)
                indexes.pop()
                steps[step] = false
            }
        }
    }
}

function Polygonal(value, step) {
    this.head = Math.floor(value / 100)
    this.tail = value % 100
    this.step = step
}

module.exports = {
    Problem061 : Problem061
};
