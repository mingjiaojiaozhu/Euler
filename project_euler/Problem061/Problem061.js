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
    let start = Math.ceil((Math.sqrt(8001) - 1) / 2)
    let end = Math.ceil((Math.sqrt(80001) - 1) / 2)
    for (let i = start; i < end; ++i) {
        let value = i * (i + 1) >>> 1
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 0))
        }
    }
}

function addSquare(polygonals) {
    let start = Math.ceil(Math.sqrt(1000))
    let end = Math.ceil(Math.sqrt(10000))
    for (let i = start; i < end; ++i) {
        let value = i * i
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 1))
        }
    }
}

function addPentagonal(polygonals) {
    let start = Math.ceil((Math.sqrt(24001) + 1) / 6)
    let end = Math.ceil((Math.sqrt(240001) + 1) / 6)
    for (let i = start; i < end; ++i) {
        let value = i * (3 * i - 1) >>> 1
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 2))
        }
    }
}

function addHexagonal(polygonals) {
    let start = Math.ceil((Math.sqrt(8001) + 1) / 4)
    let end = Math.ceil((Math.sqrt(80001) + 1) / 4)
    for (let i = start; i < end; ++i) {
        let value = i * ((i << 1) - 1)
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 3))
        }
    }
}

function addHeptagonal(polygonals) {
    let start = Math.ceil((Math.sqrt(40009) + 3) / 10)
    let end = Math.ceil((Math.sqrt(400009) + 3) / 10)
    for (let i = start; i < end; ++i) {
        let value = i * (5 * i - 3) >>> 1
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 4))
        }
    }
}

function addOctagonal(polygonals) {
    let start = Math.ceil((Math.sqrt(12002) + 2) / 6)
    let end = Math.ceil((Math.sqrt(120002) + 2) / 6)
    for (let i = start; i < end; ++i) {
        let value = i * (3 * i - 2)
        if (value % 100 >= 10) {
            polygonals.push(new Polygonal(value, 5))
        }
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
