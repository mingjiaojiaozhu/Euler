class Problem009:
    def solution(self) -> None:
        target = 1000
        for i in range(target // 3, 0, -1):
            for j in range(target >> 1, i, -1):
                remainder = target - i - j
                if i * i + j * j == remainder * remainder:
                    print(i * j * remainder)
                    return
