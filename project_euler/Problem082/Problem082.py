class Problem082:
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

        ways = [0 for _ in range(border)]
        for i in range(border):
            ways[i] = target[i][border - 1]
        for i in range(border - 2, -1, -1):
            ways[0] += target[0][i]
            for j in range(1, border):
                if ways[j] > ways[j - 1]:
                    ways[j] = ways[j - 1] + target[j][i]
                else:
                    ways[j] += target[j][i]
            for j in range(border - 2, -1, -1):
                if ways[j] > ways[j + 1] + target[j][i]:
                    ways[j] = ways[j + 1] + target[j][i]
        print(min(ways))
