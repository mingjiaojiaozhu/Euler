function Problem083() {
    let fileName = 'matrix.txt'
    let border = 80
    let target = Array(border)
    for (let i = 0; i < border; ++i) {
        target[i] = Array(border)
    }

    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    let index = 0
    while (line = handle.next()) {
        let elements = line.toString().split(' ')
        for (let [i, element] of elements.entries()) {
            target[index][i] = Number(element)
        }
        ++index
    }

    let length = border * border
    let edges = Array(length)
    for (let i = 0; i < length; ++i) {
        edges[i] = Array(length).fill(0)
    }
    for (let i = 0; i < border; ++i) {
        for (let j = 0; j < border; ++j) {
            if (i > 0) {
                edges[i * border + j][(i - 1) * border + j] = target[i - 1][j]
            }
            if (j > 0) {
                edges[i * border + j][i * border + j - 1] = target[i][j - 1]
            }
            if (i < border - 1) {
                edges[i * border + j][(i + 1) * border + j] = target[i + 1][j]
            }
            if (j < border - 1) {
                edges[i * border + j][i * border + j + 1] = target[i][j + 1]
            }
        }
    }

    let ways = Array(length)
    search(edges, length, ways)
    console.log(ways[length - 1] + target[0][0])
}

function search(edges, length, ways) {
    let visited = Array(length).fill(false)
    let queue = [new Heap(0, 0)]
    while (queue.length > 0) {
        let node = queue[0]
        let index = node.index
        let weight = node.weight
        dequeue(queue)
        if (visited[index]) {
            continue
        }

        ways[index] = weight
        visited[index] = true
        for (let i = 0; i < length; ++i) {
            if (edges[index][i] && !visited[i]) {
                enqueue(i, weight + edges[index][i], queue)
            }
        }
    }
}

function enqueue(index, weight, queue) {
    let child = queue.length
    queue.push(new Heap(0, 0))
    while (child > 0) {
        let parent = (child - 1) >>> 1
        if (queue[parent].weight <= weight) {
            break
        }
        queue[child].index = queue[parent].index
        queue[child].weight = queue[parent].weight
        child = parent
    }
    queue[child].index = index
    queue[child].weight = weight
}

function dequeue(queue) {
    let pivot = queue.pop()
    let parent = 0
    while (true) {
        let child = (parent << 1) + 1
        if (child >= queue.length) {
            break
        }

        if (child < queue.length - 1 && queue[child].weight > queue[child + 1].weight) {
            ++child
        }
        if (queue[child].weight >= pivot.weight) {
            break
        }
        queue[parent].index = queue[child].index
        queue[parent].weight = queue[child].weight
        parent = child
    }
    if (queue.length) {
        queue[parent].index = pivot.index
        queue[parent].weight = pivot.weight
    }
}

function Heap(index, weight) {
    this.index = index
    this.weight = weight
}

module.exports = {
    Problem083 : Problem083
};
