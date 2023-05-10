function Problem036() {
    let target = 1000000
    let border = Math.ceil(Math.sqrt(target))
    let palindromes = Array(2)
    let binary = []

    let result = 0
    for (let i = 1; i < border; ++i) {
        getPalindrome(i, palindromes)
        if (isBinaryPalindrome(palindromes[0], binary)) {
            result += palindromes[0]
        }
        if (isBinaryPalindrome(palindromes[1], binary)) {
            result += palindromes[1]
        }
    }
    console.log(result)
}

function getPalindrome(value, palindromes) {
    palindromes[0] = Math.floor(value / 10)
    palindromes[1] = value
    while (value) {
        palindromes[0] = palindromes[0] * 10 + value % 10
        palindromes[1] = palindromes[1] * 10 + value % 10
        value = Math.floor(value / 10)
    }
}

function isBinaryPalindrome(value, binary) {
    binary =[]
    while (value) {
        binary.push(0 !== (value & 1))
        value >>>= 1
    }

    let start = 0
    let end = binary.length - 1
    while (start < end) {
        if (binary[start] ^ binary[end]) {
            return false
        }
        ++start
        --end
    }
    return true
}

module.exports = {
    Problem036 : Problem036
};
