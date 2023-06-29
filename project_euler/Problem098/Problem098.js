function Problem098() {
    let fileName = 'words.txt'
    let wordPairs = []
    let length = getWordPair(fileName, wordPairs)

    let squares = Array(length - 2)
    for (let i = length - 3; i >= 0; --i) {
        squares[i] = new Set()
    }
    getSquares(squares, length)

    let result = 0
    let letters = Array(26)
    let digits = Array(10)
    for (let words of wordPairs) {
        let size = words[0].length
        let auxiliary = squares[size - 3]
        for (let pivot of auxiliary) {
            if (setDigits(words[0], pivot, letters, digits, size)) {
                let value = getDigits(words[1], letters)
                if (auxiliary.has(value) && (result < value || result < pivot)) {
                    result = Math.max(value, pivot)
                }
            }
        }
    }
    console.log(result)
}

function getWordPair(fileName, wordPairs) {
    let auxiliary = []
    const file = require('n-readlines')
    let handle = new file(fileName)
    let line
    while (line = handle.next()) {
        let elements = line.toString()
        if (elements.length > 2) {
            auxiliary.push(elements)
        }
    }

    let letters = Array(2)
    for (let i = 0; i < 2; ++i) {
        letters[i] = Array(26)
    }
    let result = 0
    for (let i = auxiliary.length - 1; i > 0; --i) {
        let pivot = auxiliary[i]
        getLetters(pivot, letters[0])
        let length = pivot.length
        let isPair = false
        for (let j = 0; j < i; ++j) {
            let word = auxiliary[j]
            if (length === word.length) {
                getLetters(word, letters[1])
                if (checkLetters(letters)) {
                    wordPairs.push([word, pivot])
                    isPair = true
                }
            }
        }
        if (isPair && result < length) {
            result = length
        }
    }
    return result
}

function getSquares(squares, length) {
    let border = Math.pow(10, length)
    let size = 2
    let index = 10
    while (true) {
        let value = index * index
        if (value >= border) {
            break
        }

        if (size !== Math.floor(Math.log10(value))) {
            ++size
        }
        squares[size - 2].add(value)
        ++index
    }
}

function setDigits(word, value, letters, digits, length) {
    letters.fill(-1)
    digits.fill(' ')
    for (let i = length - 1; i >= 0; --i) {
        let letter = word[i]
        let index = letter.charCodeAt(0) - 'A'.charCodeAt(0)
        let remainder = value % 10
        if ((-1 !== letters[index] && remainder !== letters[index]) || (' ' !== digits[remainder] && index !== digits[remainder])) {
            return false
        }
        letters[index] = remainder
        digits[remainder] = letter
        value = Math.floor(value / 10)
    }
    return true
}

function getDigits(word, letters) {
    let result = 0
    for (let letter of word) {
        result = result * 10 + letters[letter.charCodeAt(0) - 'A'.charCodeAt(0)]
    }
    return result
}

function getLetters(word, letters) {
    letters.fill(0)
    for (let letter of word) {
        ++letters[letter.charCodeAt(0) - 'A'.charCodeAt(0)]
    }
}

function checkLetters(letters) {
    for (let i = 0; i < 26; ++i) {
        if (letters[0][i] !== letters[1][i]) {
            return false
        }
    }
    return true
}

module.exports = {
    Problem098 : Problem098
};
