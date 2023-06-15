class Problem081:
    def solution(self) -> None:
        file_name, border = 'matrix.txt', 80
        target = [[0 for _ in range(border)] for _ in range(border)]
        with open(file_name, 'r') as handle:
            index = 0
            for line in handle:
                elements = line.strip().split(' ')
                for i, element in enumerate(elements):
                    target[index][i] = int(element)
                index += 1

        for i in range(1, border):
            target[0][i] += target[0][i - 1]
            target[i][0] += target[i - 1][0]
        for i in range(1, border):
            for j in range(1, border):
                target[i][j] += min(target[i - 1][j], target[i][j - 1])
        print(target[-1][-1])
