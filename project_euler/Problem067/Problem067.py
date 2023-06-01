class Problem067:
    def solution(self) -> None:
        file_name, border = 'triangle.txt', 100
        target = [[0 for _ in range(border)] for _ in range(border)]
        with open(file_name, 'r') as handle:
            index = 0
            for line in handle:
                elements = line.strip().split(' ')
                for i, element in enumerate(elements):
                    target[index][i] = int(element)
                index += 1

        for i in range(border - 1, 0, -1):
            for j in range(i - 1, -1, -1):
                target[i - 1][j] += max(target[i][j], target[i][j + 1])
        print(target[0][0])
