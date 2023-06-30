class Problem100:
    def solution(self) -> None:
        target, index, result = 1000000000000, 1, 1
        while index < target:
            result, index = (index << 1) + result * 3 - 2, index * 3 + (result << 2) - 3
        print(result)
