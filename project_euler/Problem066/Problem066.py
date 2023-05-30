import math
from typing import List

class Problem066:
    def solution(self) -> None:
        target, factors, result, pivot = 1000, [], 0, 0
        for i in range(5, target + 1):
            value = self.__get_solution(i, factors)
            if -1 != value and pivot < value:
                pivot, result = value, i
        print(result)

    def __get_solution(self, value: int, factors: List[int]) -> int:
        factors.clear()
        start = self.__get_period(value, factors)
        if not start:
            return -1

        previous, denominator = 0, 1
        for factor in factors:
            previous, denominator = denominator, previous + denominator * factor
        if len(factors) & 1:
            return denominator

        previous, numerator = 1, start
        for factor in factors:
            previous, numerator = numerator, previous + numerator * factor
        return numerator * denominator << 1

    def __get_period(self, value: int, factors: List[int]) -> int:
        if math.fabs(math.floor(math.sqrt(value) + 0.5) - math.sqrt(value)) < 0.00000001:
            return 0

        initial = int(math.sqrt(value))
        pivot, current, offset, factor = initial << 1, initial, 0, 1
        while current != pivot:
            offset = current * factor - offset
            factor = (value - offset * offset) // factor
            current = (initial + offset) // factor
            factors.append(current)
        factors.pop()
        return initial
