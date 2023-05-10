class Problem015:
    def solution(self) -> None:
        target = 20
        border = target << 1
        result = 1
        for i in range(border - 1, target, -2):
            result = (result << 1) * i // ((border - i + 1) >> 1)
        print(result)
