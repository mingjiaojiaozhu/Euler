class Problem006:
    def solution(self) -> None:
        target = 100
        result = target * (target - 1) * (target + 1) * (3 * target + 2) // 12
        print(result)
