import math
from typing import List

class Problem030:
    def solution(self) -> None:
        target, powers = 5, [0 for _ in range(10)]
        for i in range(0, 10):
            powers[i] = int(math.pow(i, target))

        result = 0
        for i in range(6 * powers[9], 9, -1):
            if i == self.__get_power_digit(i, powers):
                result += i
        print(result)

    def __get_power_digit(self, value: int, powers: List[int]) -> int:
        result = 0
        while value:
            result += powers[value % 10]
            value //= 10
        return result
