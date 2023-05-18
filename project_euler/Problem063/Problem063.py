import math

class Problem063:
    def solution(self) -> None:
        result = 0
        for i in range(1, 10):
            result += int(1 / (1 - math.log10(i)))
        print(result)
