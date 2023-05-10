class Problem022:
    def solution(self) -> None:
        file_name, names = 'names.txt', []
        with open(file_name, 'r') as handle:
            for line in handle:
                names.append(line.strip())

        names.sort()

        result = 0
        for i, name in enumerate(names):
            score = 0
            for letter in name:
                score += ord(letter) - ord('A') + 1
            result += score * (i + 1)
        print(result)
