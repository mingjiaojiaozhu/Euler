class Problem039:
    def solution(self) -> None:
        target, result, pivot = 1000, 0, 0
        for i in range(target, 1, -1):
            count = 0
            for j in range(i // 3, 0, -1):
                if not (((i * i) >> 1) - i * j) % (i - j) and j < (((i * i) >> 1) - i * j) // (i - j):
                    count += 1
            if pivot < count:
                pivot, result = count, i
        print(result)
