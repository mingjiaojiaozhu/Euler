import math

class Problem025:
    def solution(self) -> None:
        target = 1000
        result = math.ceil((target - 1 + math.log10(5) / 2) / math.log10((1 + math.sqrt(5)) / 2))
        print(result)
