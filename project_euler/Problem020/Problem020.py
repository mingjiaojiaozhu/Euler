class Problem020:
    def solution(self) -> None:
        target = 100
        value = target
        for i in range(target - 1, 1, -1):
            value *= i

        result = 0
        while value:
            result += value % 10
            value //= 10
        print(result)
