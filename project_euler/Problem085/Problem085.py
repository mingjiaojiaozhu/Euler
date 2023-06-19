import math

class Problem085:
    def solution(self) -> None:
        target = 2000000
        border, result, pivot = int(math.sqrt(1 + 8 * math.sqrt(target)) - 1) >> 1, 0, target
        for i in range(1, border + 1):
            length = int(math.sqrt(1 + (target << 4) / i / (i + 1)) - 1) >> 1
            value = min(abs(self.__get_count(length, i) - target), abs(self.__get_count(length + 1, i) - target))
            if pivot > value:
                result, pivot = length * i, value
        print(result)

    def __get_count(self, length: int, width: int) -> int:
        return length * (length + 1) * width * (width + 1) >> 2
