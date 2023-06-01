import math

class Problem064:
    def solution(self) -> None:
        target, result = 10000, 0
        for i in range(1, target + 1):
            if self.__get_period(i) & 1:
                result += 1
        print(result)

    def __get_period(self, value: int) -> int:
        if abs(math.floor(math.sqrt(value) + 0.5) - math.sqrt(value)) < 0.00000001:
            return 0

        initial = int(math.sqrt(value))
        pivot, current, offset, factor, count = initial << 1, initial, 0, 1, 0
        while current != pivot:
            offset = current * factor - offset
            factor = (value - offset * offset) // factor
            current = (initial + offset) // factor
            count += 1
        return count
