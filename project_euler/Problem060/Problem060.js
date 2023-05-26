function Problem060() {
    let target = 5
    let primes = []
    for (let i = 3; i < 10000; i += 2) {
        if (isPrime(i)) {
            primes.push(i)
        }
    }

    let length = primes.length
    let edges = Array(length)
    for (let i = 0; i < length; ++i) {
        edges[i] = Array(length).fill(0)
    }
    for (let i = 1; i < length; ++i) {
        let value = primes[i]
        if (checkPrime(merge(3, value), primes) && checkPrime(merge(value, 3), primes)) {
            edges[0][i] = 1
            edges[i][0] = 1
        }
    }
    for (let i = 1; i < length; ++i) {
        let pivot = primes[i]
        for (let j = i + 1; j < length; ++j) {
            let value = primes[j]
            if (pivot % 3 === value % 3 && checkPrime(merge(pivot, value), primes) && checkPrime(merge(value, pivot), primes)) {
                edges[i][j] = 1
                edges[j][i] = 1
            }
        }
    }

    let cliques = []
    let indexes = []
    for (let i = 0; i < length; ++i) {
        indexes.push(i)
    }
    search(primes, edges, cliques, indexes, target)
}

function isPrime(value) {
    if (1 !== value % 6 && 5 !== value % 6) {
        return 2 === value || 3 === value
    }

    let border = Math.floor(Math.sqrt(value))
    for (let i = 5; i <= border; i += 6) {
        if (!(value % i) || !(value % (i + 2))) {
            return false
        }
    }
    return 1 !== value
}

function checkPrime(value, primes) {
    if (value < 10000) {
        let start = 0
        let end = primes.length - 1
        while (start <= end) {
            let current = start + ((end - start) >>> 1)
            let prime = primes[current]
            if (prime === value) {
                return true
            }

            if (prime < value) {
                start = current + 1
            } else {
                end = current - 1
            }
        }
        return false
    }

    let border = Math.floor(Math.sqrt(value))
    for (let prime of primes) {
        if (prime > border) {
            break
        }
        if (!(value % prime)) {
            return false
        }
    }
    return true
}

function merge(head, tail) {
    return head * Math.floor(Math.pow(10, Math.floor(Math.log10(tail)) + 1)) + tail
}

function search(primes, edges, cliques, indexes, target) {
    if (!indexes.length) {
        if (cliques.length === target) {
            let result = 0
            for (let index of cliques) {
                result += primes[index]
            }
            console.log(result)
        }
        return
    }

    let start = indexes[0]
    for (let i = indexes.length - 1; i >= 0; --i) {
        let index = indexes[i]
        if (!edges[start][index]) {
            cliques.push(index)
            search(primes, edges, cliques, getAdjacents(edges, indexes, index), target)
            cliques.pop()
            clear(indexes, index)
        }
    }
}

function getAdjacents(edges, indexes, start) {
    let auxiliary = []
    for (let index of indexes) {
        if (edges[start][index]) {
            auxiliary.push(index)
        }
    }
    return auxiliary
}

function clear(arrays , value) {
    for (let i = arrays.length - 1; i >= 0; --i) {
        if (arrays[i] === value) {
            arrays.splice(i, 1)
        }
    }
}

module.exports = {
    Problem060 : Problem060
};
