class Problem059:
    def solution(self) -> None:
        file_name, codes, counts = 'cipher.txt', [], [{} for _ in range(3)]
        with open(file_name, 'r') as handle:
            index = 0
            for line in handle:
                code = int(line.strip())
                codes.append(code)
                if code in counts[index]:
                    counts[index][code] += 1
                else:
                    counts[index][code] = 1
                index += 1
                if 3 == index:
                    index = 0

        keys = [0 for _ in range(3)]
        for i in range(3):
            pivot = 0
            for key, value in counts[i].items():
                if pivot < value:
                    pivot, keys[i] = value, key
            keys[i] ^= ord(' ')

        result, index = 0, 0
        for code in codes:
            result += code ^ keys[index]
            index += 1
            if 3 == index:
                index = 0
        print(result)
